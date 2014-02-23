import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    Column {
        spacing: 10
        anchors.fill: parent
        PageHeader {
            title: qsTr("Registration deatils");
        }
        TextField {
            id: code;
            label: qsTr("Received SMS Code");
            inputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhDigitsOnly;
            validator: RegExpValidator { regExp: /^[0-9]{11,}$/ }
        }
        TextField {
            id: firstName;
            label: qsTr("First name");
            enabled: false;
        }
        TextField {
            id: lastName;
            label: qsTr("Last name");
            enabled: false;
        }
        Button {
            text: qsTr("Continue");
            anchors.horizontalCenter: parent.horizontalCenter;
            onClicked: {
                console.log("Registering phone...");
                telegram.registerPhoneNumber("+" + phoneNumber.text);
                pageStack.replace(Qt.resolvedUrl("WorkingPage.qml"));
            }
        }
    }
    states: State {
        name: "register_mode"
        PropertyChanges { target: firstName; enabled: true; }
        PropertyChanges { target: lastName; enabled: true; }
    }
}
