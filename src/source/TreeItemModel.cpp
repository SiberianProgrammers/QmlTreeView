/// @author Gribanov Aleksey

#include "TreeItemModel.h"
#include "RootItem.h"

#include <QDebug>

using namespace sp;

TreeItemModel::TreeItemModel()
    : QAbstractListModel(nullptr)
    , _rootItem(new RootItem(this))
{
}

//------------------------------------------------------------------------------
TreeItemModel::~TreeItemModel()
{
    if (_rootItem) {
        _rootItem->deleteLater();
        _rootItem = nullptr;
    }
}

//------------------------------------------------------------------------------
int TreeItemModel::rowCount(const QModelIndex &) const
{
    return _items.size();
}

//------------------------------------------------------------------------------
QVariant TreeItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role < 0) {
        return {};
    }

    if (index.row() >= _items.size()) {
        return {};
    }

    TreeItemInterface* item = _items.at(index.row());
    switch (role) {
        case 0: return QVariant::fromValue(item);
        case 1: return _itemsDepthHash.value(item);
        default: return {};
    }
}

//------------------------------------------------------------------------------
QHash<int, QByteArray> TreeItemModel::roleNames() const
{
    QHash<int, QByteArray> result;
    result.insert(0, QByteArrayLiteral("modelData"));
    result.insert(1, QByteArrayLiteral("itemDepth"));
    return result;
}

//------------------------------------------------------------------------------
void TreeItemModel::setRootItem(RootItem* rootItem)
{
    if (_rootItem == rootItem) {
        return;
    }

    _rootItem = rootItem;
    refillByRoot();
}

//------------------------------------------------------------------------------
void TreeItemModel::swapRow(int draggableIndex, int dropableIndex)
{
    if (draggableIndex == dropableIndex) {
        return;
    }

    auto dragItem = _items[draggableIndex];
    auto dropItem = _items[dropableIndex];

    if (dragItem->contains(dropItem, Qt::FindChildrenRecursively)
        || dropItem->isRootItem())
    {
        return;
    }

    bool moveToDown = dropableIndex > draggableIndex;
    bool moveToUp = !moveToDown;

    int dragItemChildrenSize = dragItem->childrenSize(Qt::FindChildrenRecursively);
    int destination = moveToDown
                      ? dropableIndex + 1
                      : dropableIndex;

    beginMoveRows(QModelIndex()
                 , draggableIndex
                 , draggableIndex + dragItemChildrenSize
                 , QModelIndex()
                 , destination);

    if (dragItemChildrenSize) {
        auto mid = _items.mid(draggableIndex, dragItemChildrenSize + 1);
        _items.remove(draggableIndex, dragItemChildrenSize + 1);

        for (int i = 0; i < mid.size(); ++i) {
            if (moveToDown) {
                _items.insert(draggableIndex + i + 1, mid[i]);
            } else {
                _items.insert(dropableIndex + i, mid[i]);
            }
        }
    } else {
        _items.move(draggableIndex, dropableIndex);
    }
    endMoveRows();

    int currentDepth = _itemsDepthHash[dragItem->treeParent()];
    if (dropItem->hasChildrens()) {
        if (moveToUp) {
            // This item always exists, because rootItem not move.
            dragItem->setParent(_items[dropableIndex-1]->parent());
        } else {
            dragItem->setParent(dropItem);
        }
    } else if (dragItem->parent() != dropItem->parent()) {
        dragItem->setParent(dropItem->parent());
    }

    int depthDifference = _itemsDepthHash[dragItem->treeParent()] - currentDepth;
    if (depthDifference) {
        _itemsDepthHash[dragItem] += depthDifference;

        auto childrens = dragItem->treeChildrens();
        for (const auto& child: childrens) {
            _itemsDepthHash[child] += depthDifference;
        }
    }
    emit dataChanged(createIndex(qMin(draggableIndex, dropableIndex), 0)
                   , createIndex(qMax(draggableIndex, dropableIndex) + dragItem->childrenSize(), 0)
                     , {1});
}

//------------------------------------------------------------------------------
void TreeItemModel::addItemToTargetChild(int draggableIndex, int dropableIndex)
{
    if (draggableIndex == dropableIndex) {
        return;
    }

    auto dragItem = _items[draggableIndex];
    auto dropItem = _items[dropableIndex];

    if (dragItem->contains(dropItem, Qt::FindChildrenRecursively)
        || dropItem->isRootItem())
    {
        return;
    }

    bool moveToDown = dropableIndex > draggableIndex;
    int dragItemChildrenSize = dragItem->childrenSize(Qt::FindChildrenRecursively);
    int destination = moveToDown
                      ? dropableIndex + 1
                      : dropableIndex;

    if (draggableIndex < dropableIndex || (draggableIndex + 1) > dropableIndex) {
        beginMoveRows(QModelIndex()
                     , draggableIndex
                     , draggableIndex + dragItemChildrenSize
                     , QModelIndex()
                     , destination);

        auto mid = _items.mid(draggableIndex, dragItemChildrenSize + 1);
        _items.remove(draggableIndex, dragItemChildrenSize + 1);

        int insertIndex = qMin(draggableIndex, dropableIndex) + 1;
        for (int i = 0; i < mid.size(); ++i) {
              _items.insert(insertIndex + i, mid[i]);
        }
        endMoveRows();
    }

    int currentDepth = _itemsDepthHash[dragItem->treeParent()];
    dragItem->setParent(dropItem);

    int depthDifference = _itemsDepthHash[dragItem->treeParent()] - currentDepth;
    if (depthDifference) {
        _itemsDepthHash[dragItem] += depthDifference;
        printItemDepth(dragItem);

        auto childrens = dragItem->treeChildrens();
        for (const auto& child: childrens) {
            _itemsDepthHash[child] += depthDifference;
            printItemDepth(child);
        }
    }
    emit dataChanged(createIndex(qMin(draggableIndex, dropableIndex), 0)
                   , createIndex(qMax(draggableIndex, dropableIndex) + dragItem->childrenSize(), 0));
    printTree();
}

//------------------------------------------------------------------------------
void TreeItemModel::addTreeItem(TreeItemInterface* item, int depth)
{
    _items.append(item);
    _itemsDepthHash.insert(item, depth);
    ++depth;
    for (const auto& child: item->treeChildrens()) {
        if (child) {
            addTreeItem(child, depth);
        }
    }
}

//------------------------------------------------------------------------------
void TreeItemModel::printTree()
{
    qDebug() << "==================	PRINT TREE START ==================";
    for (const auto& item: _items) {
        QString depthOffset = "   ";
        QString temp = "";
        for (int i = 0; i < _itemsDepthHash[item]; ++i) {
            temp += depthOffset;
        }

        temp += item->name();
        qDebug() << temp ;
    }

    qDebug() << "==================	PRINT TREE END	==================";
}

//------------------------------------------------------------------------------
void TreeItemModel::printItemDepth(TreeItemInterface *item)
{
    qDebug() << "item: " << item->name() << " depth: " << _itemsDepthHash[item];
}

//------------------------------------------------------------------------------
void TreeItemModel::refillByRoot()
{
    beginResetModel();
    _items.clear();

    if (!_rootItem) {
        endResetModel();
        return;
    }

    int depth = 0;
    addTreeItem(_rootItem, depth);
    endResetModel();
}
