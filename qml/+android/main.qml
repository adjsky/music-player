import QtQuick 2.15
import QtQuick.Controls 2.12

ApplicationWindow {
    property int indexOfMusic: 0
    id: root
    visible: true
    title: qsTr("Music Player")

    Interface {
        id: test

        Connections {
            target: mediaControlNotification

            function onNextButtonClicked() {
                test.playNext()
            }

            function onPreviousButtonClicked() {
                test.playPrevious()
            }

            function onPlayButtonClicked() {
                test.playButtonClick();
            }
        }
    }
}






