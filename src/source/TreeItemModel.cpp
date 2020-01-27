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
