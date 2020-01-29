import QtQuick 2.12

MouseArea {
    id: _wrapButton

    readonly property var treeItem: model.modelData
    readonly property bool isWrapped: treeItem in _treeView.wrappedDelegates
    readonly property bool isCollapsed: treeItem in _treeView.collapseDelegates

    height: parent.height
    width: height
    visible: treeItem.childrenSize > 0
    hoverEnabled: enabled
    enabled: !_treeView.flicking && !_treeView.containsDrag

    Image {
        id: icon

        anchors.fill: parent
        source: _wrapButton.containsMouse
                ? "qrc:/images/wrap_icon_hovered.png"
                : "qrc:/images/wrap_icon_unhovered.png";
    }

    //------------------------------------------------------------------------------
    onClicked: {
        if (treeItem in _treeView.wrappedDelegates) {
            var collapseDelegates = _treeView.wrappedDelegates[treeItem];
            for (var key in collapseDelegates) {
                delete _treeView.collapseDelegates[collapseDelegates[key]]
            }

            delete _treeView.wrappedDelegates[treeItem]
        } else {
            var collapseDelegates = ([])
            var childrens = treeItem.treeChildrensList();
            var keysLength = Object.keys(childrens).length;
            for (key in childrens) {
                var treeItemChild = childrens[key];

                if (!(treeItemChild in _treeView.collapseDelegates)) {
                    _treeView.collapseDelegates[treeItemChild] = keysLength - key;
                    collapseDelegates.push(treeItemChild);
                }
            }

            _treeView.wrappedDelegates[treeItem] = collapseDelegates;
        }

        _treeView.wrappedDelegatesChanged()
        _treeView.collapseDelegatesChanged()
    }

    //------------------------------------------------------------------------------
    states: [
        State {
            name: "wrap"
            when: isWrapped && !isCollapsed
            PropertyChanges {
                target: _delegate
                height: _treeView.delegateHeight
            }
            PropertyChanges {
                target: icon
                rotation: -90
            }
        }
        , State {
            name: "unwrap"
            when: !isWrapped && !isCollapsed
            PropertyChanges {
                target: _delegate
                height: _treeView.delegateHeight
            }
            PropertyChanges {
                target: icon
                rotation: 0
            }
        }
        , State {
            name: "collapse"
            when: isCollapsed
            PropertyChanges {
                target: _delegate
                height: 0
            }
        }
    ]

    //------------------------------------------------------------------------------
    transitions: [
        Transition {
            PropertyAnimation {
                duration: 50
                properties: "height, rotation"
            }
        }
    ]
}



