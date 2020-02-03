import QtQuick 2.12

MouseArea {
    id: _contextMenuButton

    property ContextMenu contextMenu: null
    readonly property real margin: 10
    property alias text: caption.text

    width: 100
    height: 20
    hoverEnabled: visible

    //------------------------------------------------------------------------------
    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    //------------------------------------------------------------------------------
    Rectangle {
        anchors.fill: parent
        color: "blue"
        opacity: 0.2
        visible: _contextMenuButton.containsMouse
    }

    //------------------------------------------------------------------------------
    Rectangle {
        height: 1
        width: parent.width
        color: "grey"
    }

    //------------------------------------------------------------------------------
    Text {
        id: caption

        font.pixelSize: 12
        anchors.left: _contextMenuButton.left
        anchors.leftMargin: margin
        anchors.verticalCenter: parent.verticalCenter
    }

    //------------------------------------------------------------------------------
    function defineContextMenu() {
        var p = parent;
        while (p) {
            if (p === undefined || p.objectName === undefined) {
                print("ContextMenuButton error in defineContextMenu. ContextMenu not found");
                break;
            }

            if (p.objectName === "ContextMenu") {
                _contextMenuButton.contextMenu = p;
                break;
            } else {
                p = p.parent;
            }
        }
    } // function defineContextMenu() {

    //------------------------------------------------------------------------------
    Component.onCompleted: {
        defineContextMenu();
    }
}
