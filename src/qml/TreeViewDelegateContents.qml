import QtQuick 2.12

//------------------------------------------------------------------------------
// Default delegate contents of TreeView.
//------------------------------------------------------------------------------
Item {
    id: _treeViewDelegateContents

    signal clicked();
    signal doubleClicked();

    TextEdit {
        id: textEdit

        property string textBackup: ""

        text: modelData.name
        font.pixelSize: 12
        width: parent.width
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        visible: height > 0

        // it is necessary, because TextEdit conflict with HoverHandler
        enabled: false

        //------------------------------------------------------------------------------
        Keys.onPressed: {
            switch (event.key) {
                case Qt.Key_Enter: event.accepted = true; saveChanges(); break;
                case Qt.Key_Return: event.accepted = true; saveChanges(); break;
                case Qt.Key_Escape: event.accepted = true; cancelChanges(); break;
            }
        }

        //------------------------------------------------------------------------------
        function saveChanges() {
            modelData.name = text;
            textEdit.text = Qt.binding(function() { return modelData.name; });
            enabled = false;
            focus = false;
        }

        //------------------------------------------------------------------------------
        function cancelChanges() {
            textEdit.text = textBackup;
            enabled = false;
            focus = false;
        }
    } // TextEdit { id: textEdit

    //------------------------------------------------------------------------------
    function activateTextEdit() {
        textEdit.enabled = true;
        textEdit.textBackup = textEdit.text
        textEdit.forceActiveFocus();
    }
}
