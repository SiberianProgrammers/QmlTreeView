///@author Gribanov Aleksey
///
#include "RootItem.h"
#include "TreeItemModel.h"

using namespace sp;

RootItem::RootItem(TreeItemModel *parent, const QUuid &id)
    : TreeItemInterface(parent, id)
{ }
