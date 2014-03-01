import QtQuick 2.0
import Sailfish.Silica 1.0
import Telegram 1.0

Page {
    PageHeader {
        id: header;
        anchors.top: parent.top;
        anchors.topMargin: Theme.paddingSmall;
        title: qsTr("Contacts");
    }

    SilicaListView {
        id: view;
        anchors { top: header.bottom; left: parent.left; right: parent.right;
            bottom: parent.bottom; topMargin: Theme.paddingMedium; }
        model: telegram.chatsModel;
        delegate: ListItem {
        }
    }
}
