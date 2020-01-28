import QtQuick 2.12

//------------------------------------------------------------------------------
// Default delegate contents of TreeView.
//------------------------------------------------------------------------------
Item {
    id: _treeViewDelegateContents

    signal clicked();
    signal doubleClicked();

    Text {
        id: textItem

        text: modelData.name
        width: parent.width
        height: parent.height
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
        anchors.fill: parent
    }
}
