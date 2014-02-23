import QtQuick 2.0
import Sailfish.Silica 1.0

WorkingPage {
    function nextPage(register_mode)
    {
        var page = pageStack.replace(Qt.resolvedUrl("WorkingPage.qml"));
        page.state = register_mode ? "register_mode" : "";
    }

    Connections {
        target: telegram;
        onCodeRequest: nextPage(false);
        onRegistrationRequested: nextPage(true);
    }
}
