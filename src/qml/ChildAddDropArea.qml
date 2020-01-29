import QtQuick 2.12

DropArea {
    id: addToChildDropArea

    width: height
    height: parent.height
    anchors.right: parent.right
    enabled: visible

    Item {
        height: 0.5*parent.height
        width: height
        anchors.centerIn: parent

        Rectangle {
            width: 1
            height: 0.75*parent.height
            color: "green"
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 1
            anchors.horizontalCenterOffset: 1
        }

        Rectangle {
            height: 1
            width: 0.75*parent.width
            color: "green"
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 1
            anchors.horizontalCenterOffset: 1
        }
    }
}
