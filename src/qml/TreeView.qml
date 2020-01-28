import QtQuick 2.12
import QtQuick.Window 2.12
import SP 1.0

ListView {
    id: _treeView

    readonly property Window window: qmlTool.parentWindow(this)
    readonly property alias qmlTool: qmlTool
    property real margin: 5
    property real depthOffset: 20
    property real delegateHeight: 20
    property var  draggableTreeItem: null

    property Component delegateContentsComponent: TreeViewDelegateContents {}

    boundsBehavior: ListView.StopAtBounds
    clip: true
    delegate: TreeViewDelegate { }

    QmlTool {
        id: qmlTool
    }
}
