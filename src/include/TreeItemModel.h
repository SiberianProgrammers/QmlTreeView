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

    public slots:
        /** Clear and fill model from _rootItem and its children. */
        void refillByRoot();

    private:
        void addTreeItem(TreeItemInterface* item, int depth);
        void printTree();
        void printItemDepth(TreeItemInterface* item);

    private:
        QVector<TreeItemInterface*> _items;
        QHash<TreeItemInterface*, int> _itemsDepthHash;
        RootItem* _rootItem = nullptr;
};

}
