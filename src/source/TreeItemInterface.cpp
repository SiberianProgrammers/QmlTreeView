///@author Gribanov Aleksey

#include "TreeItem.h"
#include "TreeItemModel.h"

#include <QObject>
#include <QChildEvent>
#include <QDebug>

using namespace sp;

TreeItemInterface::TreeItemInterface(QObject* parent, const QUuid& id)
    : QObject(parent)
    , _id(id)
{
}

//------------------------------------------------------------------------------
QVector<TreeItemInterface *> TreeItemInterface::treeChildrens() const
{
    QVector<TreeItemInterface*> vector;
    int childrenSize = children().size();
    vector.resize(childrenSize);

    for (const auto& child: findChildren<TreeItemInterface*>("", Qt::FindDirectChildrenOnly)) {
        if (child) {
            vector[child->orderIndex()] = child;
        }
    }

    return vector;
}

//------------------------------------------------------------------------------
bool TreeItemInterface::contains(TreeItemInterface *child, Qt::FindChildOption findOptions) const
{
    if (findOptions == Qt::FindDirectChildrenOnly) {
        return children().contains(child);
    } else {
        return findChildren<TreeItemInterface*>().contains(child);
    }
}

//------------------------------------------------------------------------------
TreeItemInterface *TreeItemInterface::treeParent() const
{
    return dynamic_cast<TreeItemInterface*>(parent());
}

//------------------------------------------------------------------------------
int TreeItemInterface::childrenSize(Qt::FindChildOptions findOptions) const
{
    return findChildren<TreeItemInterface*>("", findOptions).size();
}

//------------------------------------------------------------------------------
void TreeItemInterface::setName(const QString &name)
{
    if (_name != name) {
        _name = name;
        emit nameChanged();
    }
}

//------------------------------------------------------------------------------
void TreeItemInterface::setIcon(const QString &icon)
{
    if (_icon != icon) {
        _icon = icon;
        emit iconChanged();
    }
}
