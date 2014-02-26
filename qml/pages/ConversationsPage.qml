import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    PageHeader {
        id: header;
        anchors.top: parent.top;
        anchors.topMargin: Theme.paddingSmall;
        title: qsTr("Conversations");
    }
//    Column {
//        spacing: Theme.paddingMedium;
//        anchors.fill: parent
//        anchors.margins: Theme.paddingSmall;

//    }
    ListView {
        id: view;
        anchors.top: header.bottom;
        anchors.topMargin: Theme.paddingMedium;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        model: telegram.chatsModel;
        delegate: Text {
            width: 100;
            height: 100;
            text: "hola";
            Component.onCompleted: console.log("olaKase?");
        }
    }

    Component.onCompleted: {
        console.log("el modelo es: " + view.model)
        console.log("el modelo es: " + telegram.chatsModel);
        console.log("count: " + view.count);
    }
}
