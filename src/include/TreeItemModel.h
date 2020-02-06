/// @author Gribanov Aleksey

#include "TreeItemInterface.h"
#include "RootItem.h"

#include <QAbstractListModel>

namespace sp {

/***************************************************************************//**
 * @brief Model for providing data of item in TreeView.
 ******************************************************************************/
class TreeItemModel: public QAbstractListModel
{
    Q_OBJECT

    public:
        TreeItemModel();
        ~TreeItemModel() override;

        //------------------------------------------------------------------------------
        // Override
        //------------------------------------------------------------------------------
        int rowCount (const QModelIndex & parent = QModelIndex()) const final;
        QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const final;
        QHash<int, QByteArray> roleNames() const final;

        //------------------------------------------------------------------------------
        // Get
        //------------------------------------------------------------------------------
        /** Returns RootItem for this model. */
        inline RootItem* rootItem() const { return _rootItem; }

        //------------------------------------------------------------------------------
        // Special
        //------------------------------------------------------------------------------
        /** Sets RootItem for this model. */
        Q_INVOKABLE void setRootItem(RootItem* rootItem);

        /** Swap row with the draggableIndex from row with the dropableIndex. */
        Q_INVOKABLE void swapRow(int draggableIndex, int dropableIndex);

        /**
         * Appended item with draggableIndex to childrens of item with dropableIndex
         * and change row order.
         */
        Q_INVOKABLE void addItemToTargetChild(int draggableIndex, int dropableIndex);

        /** Removes treeItem from this model. */
        Q_INVOKABLE void removeItem(TreeItemInterface* treeItem);

    public slots:
        /** Clear and fill model from _rootItem and its children. */
        void refillByRoot();

    private:
        void addTreeItem(TreeItemInterface* item, int depth);
        void printTree();
        void printItemDepth(TreeItemInterface* item);
        void fixTreeItemsOrderIndex();

    private:
        QVector<TreeItemInterface*> _items;
        QHash<TreeItemInterface*, int> _itemsDepthHash;
        RootItem* _rootItem = nullptr;
};

}
