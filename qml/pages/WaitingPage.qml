import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: page;
    property alias label: label.text;

    BusyIndicator {
        id: busyIndicator;
        running: true;
        anchors.centerIn: parent;
        size: BusyIndicatorSize.Large;
    }

    Label {
        id: label;
        anchors.top: busyIndicator.bottom;
        anchors.topMargin: 10;
        anchors.horizontalCenter: parent.horizontalCenter;
    }
}
