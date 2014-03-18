import QtQuick 2.0
import Sailfish.Silica 1.0
import Telegram 1.0

Column {
    property alias userName: userName.text;
    property alias message: label.text;
    spacing: Theme.paddingSmall;
    height: childrenRect.height;
    anchors.left: parent.left; anchors.right: parent.right;
    anchors.leftMargin: Theme.paddingSmall;
    anchors.rightMargin: Theme.paddingSmall;

    Label {
        DebugRect {}
        id: userName;
        color: Theme.primaryColor;
        font: label.font;
    }

    Label {
        DebugRect {}
        id: label;
        color: Theme.secondaryColor;
        wrapMode: Text.WordWrap;
        font.pixelSize: Theme.fontSizeExtraSmall;
    }
}
