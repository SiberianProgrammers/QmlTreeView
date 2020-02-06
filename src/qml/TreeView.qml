import QtQuick 2.12
import QtQuick.Window 2.12
import SP 1.0

ListView {
    id: _treeView

    readonly property Window window: qmlTool.parentWindow(this)
    readonly property alias qmlTool: qmlTool
    readonly property alias contextMenu: contextMenu
    readonly property alias activeFlick: flickDropArea.activeFlick
    readonly property bool  containsDrag: draggableTreeItem !== null
    property alias contextMenuButtons: contextMenu.buttons

    // Move this properties to another place
    property var wrappedDelegates: ({})
    property var collapseDelegates: ({})

    // Consts
    property real margin: 5
    property real depthOffset: 20
    property real delegateHeight: 20
    property var  draggableTreeItem: null
    property Item draggableDelegate: null
    property Component delegateContentsComponent: TreeViewDelegateContents {}
    property int wrapAnimationDuration: 50

    boundsBehavior: ListView.StopAtBounds
    clip: true
    delegate: TreeViewDelegate { }

    QmlTool {
        id: qmlTool
    }

    FlickDropArea {
        id: flickDropArea

        anchors.fill: parent
        target: _treeView
        enabled: draggableTreeItem !== null
    }

    ContextMenu {
        id: contextMenu
    }
}
