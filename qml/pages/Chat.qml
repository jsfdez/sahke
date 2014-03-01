import QtQuick 2.0
import Sailfish.Silica 1.0
import Telegram 1.0

Page {
    id: page;
    function loadChat(type, id)
    {
        console.log("Loading chat");
        chat.loadChat(type, id);
    }

    Chat {
        id: chat;
    }


    PageHeader {
        id: header;
        anchors.top: parent.top;
        anchors.topMargin: Theme.paddingSmall;
        title: qsTr("Conversation");
    }

    SilicaListView {
        id: view;
        anchors { top: header.bottom; left: parent.left; right: parent.right;
            bottom: parent.bottom; topMargin: Theme.paddingMedium; }
        model: chat;
        delegate: ListItem {
            id: listItem;
            width: parent.width;
            contentHeight: label.height;
            Column {
                anchors.left: parent.left; anchors.right: parent.right;
                anchors.leftMargin: Theme.paddingSmall;
                anchors.rightMargin: Theme.paddingSmall;

                Text {
                    id: userName;
                }

                Label {
                    id: label;
                    anchors.left: parent.left; anchors.right: parent.right;
                    wrapMode: Text.WordWrap;
                    text: message;
                    font.pixelSize: Theme.fontSizeExtraSmall;
                }
            }

        }
    }
}
