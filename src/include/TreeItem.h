///@author Gribanov Aleksey

#pragma once

#include "TreeItemInterface.h"

namespace sp {

class TreeItem: public TreeItemInterface
{
    public:
        TreeItem(TreeItemInterface* parent, const QUuid& id = QUuid::createUuid())
            : TreeItemInterface(parent, id)
        {
            if (parent) {
                _orderIndex = parent->children().size() - 1;
            }
        }

        inline bool isRootItem() const override { return false; }
};
}
