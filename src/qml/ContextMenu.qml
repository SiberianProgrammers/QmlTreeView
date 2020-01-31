import QtQuick 2.12
import QtQuick.Window 2.12

MouseArea {
    id: _contextMenu

    readonly property Window window: qmlTool.parentWindow(this)
    default property alias buttons: menu.data

    property point cursorPoint: Qt.point(0,0)
    property Item selectedTreeItemDelegate: null
    property var selectedTreeItem: null

    visible: false
    hoverEnabled: visible
    anchors.fill: parent
    acceptedButtons: Qt.LeftButton | Qt.RightButton

    //------------------------------------------------------------------------------
    Rectangle {
        color: "black"
        opacity: 0.75
        anchors.fill: parent
    }

    //------------------------------------------------------------------------------
    Column {
        id: menu

        x: cursorPoint.x
        y: cursorPoint.y
    }

    //------------------------------------------------------------------------------
    Rectangle {
        color: "transparent"
        anchors.fill: menu
        border.color: "gray"
        border.width: 1
    }

    //------------------------------------------------------------------------------
    Loader {
        id: defaultMenuLoader

        x: cursorPoint.x
        y: cursorPoint.y
    }

    //------------------------------------------------------------------------------
    onClicked:  {
        _contextMenu.close();
    }

    //------------------------------------------------------------------------------
    states: [
        State {
            name: "opened"
            when: _contextMenu.visible

            ParentChange {
                target: _contextMenu
                parent: _contextMenu.window.contentItem
            }
        }
    ]

    //------------------------------------------------------------------------------
    function open() {
        cursorPoint = qmlTool.cursorPosInItem(window.contentItem)
        visible = true;
    }

    //------------------------------------------------------------------------------
    function close() {
        visible = false;
    }

    Component.onCompleted: {
        if (menu.children.length === 0) {
            defaultMenuLoader.source = "qrc:/sp/ContextMenuButtonsDefault.qml"
        }
    }
}
