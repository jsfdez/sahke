# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed

#   DEBUG in device -> %define debug_package %{nil}
TEMPLATE = subdirs

CONFIG += sailfishapp

SUBDIRS += 3rdParty/tg/tg.pro \
    src

OTHER_FILES += rpm/sahke.spec \
    rpm/sahke.yaml \
    qml/sahke.qml \
    qml/cover/CoverPage.qml \
    qml/pages/PhoneNumberPage.qml \
    qml/pages/WorkingPage.qml \
    qml/pages/RegisteringPage.qml \
    qml/pages/UserDetailsPage.qml \
    qml/pages/WaitingPage.qml \
    qml/pages/ConversationsPage.qml \
    qml/pages/ContactsPage.qml \
    qml/pages/Chat.qml \
    sahke.desktop
    3rdParty/tg/server.pub

pubkeys.files = 3rdParty/tg/server.pub
pubkeys.path = /etc/$${TARGET}

INSTALLS += pubkeys
