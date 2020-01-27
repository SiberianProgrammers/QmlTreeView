import QtQuick 2.12

Rectangle {
    id: _delegate

    readonly property real xOffset: _treeView.margin + model.itemDepth*_treeView.depthOffset
    readonly property var treeItem: model.modelData

    width: _treeView.width
    height: _treeView.delegateHeight

    //------------------------------------------------------------------------------
    Item {
        id: _treeViewDelegateContents

        anchors.fill: parent
        anchors.leftMargin: _delegate.xOffset

        Text {
            id: textItem

            text: treeItem.name
            width: parent.width
            height: parent.height
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
        }
    }
}
