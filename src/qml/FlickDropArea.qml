import QtQuick 2.12

Item {
    id: _flickDropArea

    property Flickable target: null
    property int dropAreaHeight: 0.75*_treeView.delegateHeight
    property int flickStep: 5
    readonly property alias activeFlick: _p.activeFlick
    readonly property real maxContentY: target != null
                                        ? target.contentHeight - target.height
                                        : 0

    //------------------------------------------------------------------------------
    DropArea {
        id: topDropArea

        width: parent.width
        height: _flickDropArea.dropAreaHeight
        enabled: _flickDropArea.enabled
                 && target.contentY > 0

        onEntered: { _p.run(-_flickDropArea.flickStep); }
        onExited: { _p.stop(); }
    }

    //------------------------------------------------------------------------------
    DropArea {
        id: bottomDropArea

        width: parent.width
        height: _flickDropArea.dropAreaHeight
        anchors.bottom: parent.bottom
        enabled: _flickDropArea.enabled
                 && target.contentY < _flickDropArea.maxContentY

        onEntered: { _p.run(_flickDropArea.flickStep); }
        onExited:  { _p.stop(); }
    }

    //------------------------------------------------------------------------------
    Timer {
        id: moveTimer

        property int moveDelta: 0

        interval: 0

        onTriggered: {
            interval = Math.min(25, interval + 5);
            var newContentY = target.contentY + moveDelta;
            var oldContentY = target.contentY
            target.contentY = Math.max(0, Math.min(newContentY, maxContentY))
            if (oldContentY === target.contentY) {
                _p.stop();
            } else {
                start();
            }
        }
    } // Timer { id: moveTimer

    //------------------------------------------------------------------------------
    QtObject {
        id: _p

        property bool activeFlick: false
        property point treeViewPos: _treeView.draggableTreeItem !== null
                                    ? _treeView.window.contentItem.mapToItem(_treeView,0,0)
                                    : Qt.point(0,0)

        //------------------------------------------------------------------------------
        function stop() {
            activeFlick = false;
            moveTimer.interval = 0;
            moveTimer.stop();
        }

        //------------------------------------------------------------------------------
        function run(delta) {
            if (moveTimer.running) {
                return;
            }

            moveTimer.moveDelta = delta;
            moveTimer.start();
        }

        //------------------------------------------------------------------------------
        function checkMousePos() {
            if (activeFlick) {
                return;
            }

            var dragPoint = _treeView.draggableDelegate.Drag.hotSpot
            var cursorX = _treeView.draggableDelegate.x + dragPoint.x
            var cursorY = _treeView.draggableDelegate.y + dragPoint.y

            var checkX = cursorX >= _p.treeViewPos.x
                      && cursorX <= (_p.treeViewPos.x + _treeView.width)
            var checkY = (cursorY + dropAreaHeight) >= _p.treeViewPos.y
                      && cursorY <= (_p.treeViewPos.y + _treeView.height - dropAreaHeight)

            _p.activeFlick = checkX & checkY
        }
    } // QtObject { id: _p

    Connections {
        target: _treeView.draggableDelegate
        onXChanged: { _p.checkMousePos(); }
        onYChanged: { _p.checkMousePos(); }
    }
}
