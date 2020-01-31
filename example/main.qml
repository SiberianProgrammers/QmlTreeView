import QtQuick 2.12
import QtQuick.Window 2.12

import "qrc:/sp"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QmlTreeView example")

    TreeView {
        id: treeView

        model: TreeItemModel
        width: 200
        height: 0.85*parent.height
        anchors.centerIn: parent

        // Example of how to override standard context menu button
        //contextMenuButtons: [
        //    ContextMenuButton { text: qsTr("Element 1") }
        //    , ContextMenuButton { text: qsTr("Element 2") }
        //]
    }

    Rectangle {
        anchors.fill: treeView
        border.color: "grey"
        border.width: 1
        color: "transparent"
    }
}
