import QtQuick 2.0
import Sailfish.Silica 1.0
import Telegram 1.0

Page {
    PageHeader {
        id: header;
        anchors.top: parent.top;
        anchors.topMargin: Theme.paddingSmall;
        title: qsTr("Conversations");
    }

    SilicaListView {
        id: view;
        anchors { top: header.bottom; left: parent.left; right: parent.right;
            bottom: parent.bottom; topMargin: Theme.paddingMedium; }
        model: telegram.chatsModel;
        delegate: ListItem {
            id: listItem;
            width: parent.width;
            contentHeight: Theme.itemSizeMedium;
            menu: ContextMenu { MenuItem { text: "Remove"; onClicked: remove(); } }
            Text {
                text: lastMessage;
                font.pixelSize: label.font.pixelSize;
                font.bold: true;
                anchors.fill: parent;
                anchors.leftMargin: Theme.paddingSmall;
                anchors.rightMargin: Theme.paddingSmall;
                opacity: 0.05;
                color: "white";
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere;
                elide: Text.ElideRight;
            }
            ListView.onRemove: animateRemoval(listItem);
            function remove() {
                remorseAction("Deleting", function() { view.model.remove(index); } );
            }

            Rectangle {
                id: labelDebugRect;
                anchors.fill: label;
                color: "pink";
                visible: debug;
            }

            Label {
                id: label;
                anchors.centerIn: parent;

                text: peerType === ChatsModel.User ? firstName + " " + lastName
                                                   : groupName;
            }

            onClicked: {
                console.log("Opening chat...");
                telegram.chatInfo(peerType, index);
            }
        }
    }
}
