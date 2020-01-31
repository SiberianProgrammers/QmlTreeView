import QtQuick 2.12

Rectangle {
    id: _contextMenuButtonsDefault

    border.color: "gray"
    border.width: 1
    width: column.width
    height: column.height

    Column {
        id: column

        //------------------------------------------------------------------------------
        ContextMenuButton {
            text: qsTr("Rename")

            onClicked: {
                contextMenu.selectedTreeItemDelegate.activateTextEdit();
                contextMenu.close();
            }
        } // ContextMenuButton {

        //------------------------------------------------------------------------------
        ContextMenuButton {
            text: qsTr("Delete")

            onClicked: {
                var model = _treeView.model;
                var item = contextMenu.selectedTreeItem;
                model.removeItem(item);
                contextMenu.close();
            }
        } // ContextMenuButton {
    }
}
