///@author Gribanov Aleksey
#pragma once

#include "TreeItemInterface.h"

namespace sp {

class TreeItemModel;
class RootItem: public TreeItemInterface
{
    public:
        RootItem(TreeItemModel* parent, const QUuid& id = QUuid::createUuid());

        inline bool isRootItem() const override { return true;}
};

}
