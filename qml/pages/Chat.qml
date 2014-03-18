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
        title: chat.title;
    }

    SilicaListView {
        id: view;
        anchors { top: header.bottom; left: parent.left; right: parent.right;
            bottom: sendBox.top; topMargin: Theme.paddingMedium; }
        model: chat;
        clip: true;
        verticalLayoutDirection: ListView.BottomToTop;
        delegate: ListItem {
            id: listItem;
            width: parent.width;
            contentHeight: chatDelegate.height;
            ChatDelegate {
                id: chatDelegate;
                userName: from;
                message: text

                states: [
                    State { when: action === Chat.ChatAddUser; PropertyChanges { target: chatDelegate; message: "added a user"; } },
                    State { when: action === Chat.ChatChangePhoto; PropertyChanges { target: chatDelegate; message: "changed photo"; } },
                    State { when: action === Chat.ChatChangeTitle; PropertyChanges { target: chatDelegate; message: "changed title"; } },
                    State { when: action === Chat.ChatCreated; PropertyChanges { target: chatDelegate; message: "created the chat"; } },
                    State { when: action === Chat.ChatDeletePhoto; PropertyChanges { target: chatDelegate; message: "deleted the photo"; } },
                    State { when: action === Chat.ChatDeleteUser; PropertyChanges { target: chatDelegate; message: "user deleted"; } }
                ]
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
