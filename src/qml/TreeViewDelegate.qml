import QtQuick 2.12

Rectangle {
    id: _delegate

    readonly property real xOffset: _treeView.margin + model.itemDepth*_treeView.depthOffset
    readonly property var treeItem: model.modelData

    width: _treeView.width
    height: _treeView.delegateHeight

    //------------------------------------------------------------------------------
    DropArea {
        id: swapDropArea

        width: 0.75*_treeView.width
        height: _delegate.height
        enabled: height > 0
        visible: enabled && !_treeView.activeFlick

        onEntered: {
            TreeItemModel.swapRow(drag.source.visualIndex, index)
        }
    } // DropArea { id: swapDropArea

    //------------------------------------------------------------------------------
    Loader {
        id: delegateContentsLoader

        readonly property var modelData: model.modelData

        anchors.fill: parent
        anchors.leftMargin: _delegate.xOffset
        opacity: 0.5
        visible: draggableTreeItem !== null
        sourceComponent: _treeView.delegateContentsComponent
    } // Loader { id: delegateContentsLoader

    //------------------------------------------------------------------------------
    TreeViewDraggableDelegate {
        id: draggableDelegate

        Rectangle {
            anchors.fill: parent
            color: "blue"
            opacity: 0.2
            visible: hoverHandler.hovered || wrapButton.containsMouse
        }

        HoverHandler {
            id: hoverHandler

            target: draggableDelegate
            enabled: !_treeView.flicking && !wrapButton.containsMouse
        }
    } // TreeViewDraggableDelegate { id: draggableDelegate

    //------------------------------------------------------------------------------
    Rectangle {
        width: parent.width
        height: 1
        visible: index > 0
        color: "grey"
    }

    //------------------------------------------------------------------------------
    Rectangle {
        width: parent.width
        height: 1
        visible: index === _treeView.count - 1
        color: "grey"
        anchors.bottom: parent.bottom
    }

    //------------------------------------------------------------------------------
    WrapButton {
        id: wrapButton

        anchors.left: parent.left
        anchors.leftMargin: _delegate.xOffset - width
    } // WrapButton {

    //------------------------------------------------------------------------------
    ChildAddDropArea {
        visible: height > 0
                 && _treeView.draggableTreeItem !== null
                 && _treeView.draggableTreeItem !== treeItem
                 && treeItem.childrenSize === 0
                 && !treeItem.containsParent(_treeView.draggableTreeItem)

        onEntered: {
            TreeItemModel.addItemToTargetChild(drag.source.visualIndex, index)
        }
    } // ChildAddDropArea {
}
