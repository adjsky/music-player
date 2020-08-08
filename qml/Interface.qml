import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtMultimedia 5.15
import PlaylistModel 1.0

Item {
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent

        ListView {
            focus: true
            flickableDirection: Flickable.VerticalFlick
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            id: playView
            model: playlistmodel

            Layout.fillHeight: true
            Layout.fillWidth: true
            currentIndex: -1

            delegate: Rectangle {
                id: delegate
                width: root.width
                height: 40
                color: ListView.isCurrentItem ? "red" : "white"

                Text {
                    text: model.name.replace(/.\w+$/, "")
                    font.pixelSize: 11
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked:  {
                        root.indexOfMusic = index
                        startPlaying()
                    }
                }
            }
        }

        RowLayout {
            id: progressrow
            Layout.margins: 5
            Layout.fillWidth: true

            MySlider {
                id: progressbar
                from: 0
                Layout.fillWidth: true
                sliderColor: 'red'
                sliderHeight: 7
                sliderRadius: 5
            }




    // put two text types instead of one because i get text bug when i call two functions to get time
            Text {
                text: getTextDuration(progressbar.value) + ' / '
            }

            Text {
                text: getTextDuration(playMusic.duration)
            }
        }

        RowLayout {
            id: controls
            Layout.fillWidth: true
            Layout.margins: 5

            Row {

                Button {
                    id: prevbtn
                    text: 'Previous'

                    onClicked: {
                        playPrevious()
                        statebtn.text = 'Pause'
                    }
                }

                Button {
                    id: statebtn
                    text: 'Play'
                    onClicked: {
                        playButtonClick();
                    }
                }

                Button {
                    id: nextbtn
                    text: 'Next'

                    onClicked: {
                        playNext()
                        statebtn.text = 'Pause'
                    }
                }
            }

            Slider {
                Layout.fillWidth: true
                from: 0
                to: 100
                value: 100

                onMoved: {
                    playMusic.volume = value / 100
                }
            }

            Button {
                text: "Shuffle"

                onClicked: {
                    playlistmodel.shufflePlaylist()
                    indexOfMusic = 0
                    startPlaying()
                }
            }
        }
    }

    PlaylistModel {
        id: playlistmodel
    }


    Audio {
        id: playMusic
        source: ""
    }

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            if (progressbar.value === playMusic.duration && playMusic.source != "")
                playNext()

            progressbar.value = playMusic.position
        }
    }   

    function playNext() {
        if (indexOfMusic === playlistmodel.rowCount() - 1)
            indexOfMusic = 0
        else
            indexOfMusic += 1
        startPlaying()
    }
    function playPrevious() {
        if (indexOfMusic == 0 || playMusic.source == "")
            indexOfMusic = playlistmodel.rowCount() - 1
        else
            indexOfMusic -= 1
        startPlaying()
    }

    function getTextDuration(dur) {
        let minutes = Math.trunc(dur / 60000)
        let seconds = (dur % 60000).toString()
        if (seconds < 1000) {
            seconds = "00"
        } else if (seconds < 10000) {
            seconds = "0".concat(seconds[0])
        } else {
            seconds = seconds.substring(0, 2)
        }
        return minutes + ':' + seconds
    }

    function playButtonClick() {
        if (playMusic.playbackState == Audio.PlayingState) {
            playMusic.pause()
            statebtn.text = 'Play'
            if (Qt.platform.os == "android")
                mediaControlNotification.notificate(playlistmodel.nameAt(indexOfMusic).replace(/.\w+$/, ""), true)
        } else {
            statebtn.text = 'Pause'
            playMusic.play()
            if (Qt.platform.os == "android")
                mediaControlNotification.notificate(playlistmodel.nameAt(indexOfMusic).replace(/.\w+$/, ""), false)
        }
    }

    function startPlaying() {
        statebtn.text = 'Pause'
        playMusic.source = playlistmodel.urlAt(indexOfMusic)
        playMusic.play()
        playView.currentIndex = indexOfMusic
        progressbar.value = 0
        if (Qt.platform.os == "android")
            mediaControlNotification.notificate(playlistmodel.nameAt(indexOfMusic).replace(/.\w+$/, ""), false)
    }
}
