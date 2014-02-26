import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    Column {
        spacing: Theme.paddingMedium;
        anchors.fill: parent
        anchors.margins: Theme.paddingLarge;
        PageHeader {
            title: qsTr("Registration deatils");
        }
        TextField {
            id: code;
            label: "Received SMS Code";
            placeholderText: label;
            anchors.left: parent.left;
            anchors.right: parent.right;
            inputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhDigitsOnly;
            validator: RegExpValidator { regExp: /^[0-9]{5,}$/ }
        }
        TextField {
            id: firstName;
            label: "First name";
            placeholderText: label;
            anchors.left: parent.left;
            anchors.right: parent.right;
            enabled: false;
        }
        TextField {
            id: lastName;
            label: "Last name";
            placeholderText: label;
            anchors.left: parent.left;
            anchors.right: parent.right;
            enabled: false;
        }
        Button {
            text: qsTr("Continue");
            enabled: code.acceptableInput;
            anchors.horizontalCenter: parent.horizontalCenter;
            onClicked: {
                console.log("Registering phone...");
                telegram.completeRegistration(code.text, firstName.text,
                                              lastName.text);
                pageStack.pop(null, PageStackAction.Immediate);
            }
        }
    }
    states: State {
        name: "register_mode"
        PropertyChanges { target: firstName; enabled: true; }
        PropertyChanges { target: lastName; enabled: true; }
    }
}
