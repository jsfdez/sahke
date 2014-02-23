import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    property alias label: label;

    BusyIndicator {
        id: busyIndicator;
        running: true;
        anchors.centerIn: parent;
        size: BusyIndicatorSize.Large;
    }

    Label {
        id: label;
        text: qsTr("Authorizing phone...");
        anchors.top: busyIndicator.bottom;
        anchors.topMargin: 10;
        anchors.horizontalCenter: parent.horizontalCenter;
    }

    Connections {
        target: telegram;
        onAuthorizedPhone: {
        }
    }
}
