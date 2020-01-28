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
    }
}
