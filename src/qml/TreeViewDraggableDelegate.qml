import QtQuick 2.12

Rectangle {
    id: _treeViewDraggableDelegate

    readonly property int visualIndex: index
    readonly property var treeItem: model.modelData
    property point pressedCursorPos: Qt.point(0,0)

    width: _delegate.width
    height: _delegate.height
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter

    Drag.active: dragHandler.active

    //------------------------------------------------------------------------------
    DragHandler {
        id: dragHandler

        xAxis.enabled: true
        yAxis.enabled: true
        acceptedButtons: Qt.LeftButton

        onActiveChanged: {
            if (!active) {
                recreateMouseArea();
            }
        }
    } // DragHandler { id: dragHandler

    //------------------------------------------------------------------------------
    Loader {
        id: delegateContentLoader

        readonly property var modelData: model.modelData

        anchors.fill: parent
        anchors.leftMargin: _delegate.xOffset
        sourceComponent: _treeView.delegateContentsComponent
    }

    //------------------------------------------------------------------------------
    Image {
        id: draggableIcon

        source: ""
        height: parent.height
        width: 8
        fillMode: Image.PreserveAspectFit
    }

    //------------------------------------------------------------------------------
    // MouseArea is wrapped by Loader, because mouseArea doesn't responce on press after any
    // drag action.
    // After any drag action MouseArea must be recreated.
    //------------------------------------------------------------------------------
    Loader {
        id: mouseAreaLoader

        anchors.fill: parent

        sourceComponent: Component {
            id: mouseAreaComponent

            MouseArea {
                propagateComposedEvents: true
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onPressed: {
                    if (mouse.button === Qt.RightButton) {
                        // show context menu
                        mouse.accepted = true;
                        _treeView.contextMenu.selectedTreeItemDelegate = delegateContentLoader.item
                        _treeView.contextMenu.selectedTreeItem = model.modelData
                        _treeView.contextMenu.open();
                        return;
                    }

                    // save cursor position for define correct Drag.hotSpot
                    pressedCursorPos = qmlTool.cursorPosInItem(_treeViewDraggableDelegate)

                    // it is necessary so that the ListView does not scroll vertically
                    mouse.accepted = true;
                }

                onClicked: {
                    delegateContentLoader.item.clicked();
                }

                onDoubleClicked:  {
                    delegateContentLoader.item.doubleClicked();
                }
            } // MouseArea {
        }
    } // Loader { id: mouseAreaLoader

    states: [
        State {
            name: "draggable"
            when: _treeViewDraggableDelegate.Drag.active

            ParentChange {
                target: _treeViewDraggableDelegate
                parent: _treeView.window.contentItem
                x: _treeView.window.contentItem.mapToItem(_treeView, 0, 0).x
                y: _treeView.window.contentItem.mapToItem(_treeView, 0, 0).y
            }

            PropertyChanges {
                target: _treeView
                draggableTreeItem: treeItem
                draggableDelegate: _treeViewDraggableDelegate
            }

            PropertyChanges {
                target: dragHandler
                enabled: true
            }

            PropertyChanges {
                target: _treeViewDraggableDelegate
                opacity: 0.75
                Drag.hotSpot.x: pressedCursorPos.x
                Drag.hotSpot.y: pressedCursorPos.y
            }

            AnchorChanges {
                target: _treeViewDraggableDelegate
                anchors.verticalCenter: undefined
                anchors.horizontalCenter: undefined
            }
        }
        , State {
            name: "parentDraggable"
            when: _treeView.draggableTreeItem !== null
                  && treeItem.containsParent(_treeView.draggableTreeItem)

            PropertyChanges {
                target: _treeViewDraggableDelegate
                opacity: 0.1
            }

            PropertyChanges {
                target: dragHandler
                enabled: false
            }
        }
    ] // states: [

    function recreateMouseArea() {
        mouseAreaLoader.sourceComponent = undefined;
        mouseAreaLoader.sourceComponent = mouseAreaComponent;
    }
} // Rectangle { id: _treeViewDraggableDelegate
