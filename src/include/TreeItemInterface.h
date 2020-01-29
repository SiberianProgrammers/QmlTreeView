///@author Gribanov Aleksey
#pragma once

#include <QString>
#include <QObject>
#include <QUuid>
#include <QVector>

/***************************************************************************//**
 * @brief Abstract interface of item for displaing in TreeView.
 ******************************************************************************/
class TreeItemInterface: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(bool isRootItem READ isRootItem CONSTANT)
    Q_PROPERTY(int  childrenSize READ childrenSize NOTIFY childrenChanged)

    public:
        TreeItemInterface(QObject* parent, const QUuid& id = QUuid::createUuid());

        //------------------------------------------------------------------------------
        // Virtual
        //------------------------------------------------------------------------------
        /** Returns name of the item. */
        inline virtual const QString& name() const { return _name; }

        /** Returns icon source (resouce path) of the item. */
        inline virtual const QString& icon() const { return _icon; }

        /** Returns true, if item is the RootItem. */
        inline virtual bool isRootItem() const = 0;

        //------------------------------------------------------------------------------
        // Get
        //------------------------------------------------------------------------------
        /** Returns name of this item. */
        inline const QUuid& id() const { return _id; }

        /** Returns order index in children list of the item's parent. */
        inline int orderIndex() const { return _orderIndex; }

        /** Returns true, if item has chilren. */
        inline bool hasChildrens() const { return childrenSize() > 0;}

        /** Returns children size for this item. */
        int childrenSize(Qt::FindChildOptions findOptions = Qt::FindDirectChildrenOnly) const;

        /** Returns array of children for this item. */
        QVector<TreeItemInterface*> treeChildrens() const;

        /** Return true, if this item contains child. */
        Q_INVOKABLE bool contains(TreeItemInterface* child, Qt::FindChildOption findOptions = Qt::FindDirectChildrenOnly) const;

        /** Return parent for this item. */
        Q_INVOKABLE TreeItemInterface* treeParent() const;

        Q_INVOKABLE QList<QObject*> treeChildrensList() const;

        //------------------------------------------------------------------------------
        // Set
        //------------------------------------------------------------------------------
        /** Sets name for this item.*/
        void setName(const QString& name);

        /** Sets icon for this item.*/
        void setIcon(const QString& icon);

    signals:
        void nameChanged();
        void iconChanged();
        void childrenChanged();

    protected:
        QUuid _id;
        QString _name;
        QString _icon;
        int _orderIndex = 0;
};
