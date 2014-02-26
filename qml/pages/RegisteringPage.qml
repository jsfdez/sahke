import QtQuick 2.0
import Sailfish.Silica 1.0

WorkingPage {
    function nextPage(register_mode)
    {
        console.log("Next page!");
        var page = pageStack.replace(Qt.resolvedUrl("WorkingPage.qml"));
        page.state = register_mode ? "register_mode" : "";
    }

    Component.onCompleted: {
        console.log("Waiting for SMS...");
    }

    Connections {
        target: telegram;
        onCodeRequested: nextPage(false);
        onRegistrationRequested: nextPage(true);
    }
}
