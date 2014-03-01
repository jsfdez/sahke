import QtQuick 2.0
import Sailfish.Silica 1.0
import Telegram 1.0
import "EmojiTextArea"

Page {
    id: page;
    property bool sendByEnter: true;
    property alias editor: sendBox;

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
            bottom: sendBox.bottom; topMargin: Theme.paddingMedium; }
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

    TextArea {
        id: sendBox;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: sendButton.left;
        label: qsTr("Enter the message");
        focus: true;
        placeholderText: label;
    }

    Button {
        id: sendButton;
        text: qsTr("Send");
        Label {
            id: sendButtonText;
            visible: false;
            text: parent.text;
        }
        width: sendButtonText.paintedWidth + Theme.paddingSmall;
        anchors.right: parent.right;
        anchors.verticalCenter: sendBox.verticalCenter;
        onClicked: {
            console.log("Seding...");
            chat.sendText(sendBox.text);
            sendBox.text = "";
        }
    }
}
