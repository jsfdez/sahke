import QtQuick 2.0

Rectangle {
    anchors.fill: parent;
    z: -1;
    opacity: 0.25;
    color: Math.round(Math.random()) == 1 ? Qt.rgba(1, 0, 0, 0)
                                          : Qt.rgba(0, 0, 1, 0);
}
