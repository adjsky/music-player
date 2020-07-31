import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtMultimedia 5.15
import PlaylistModel 1.0


ApplicationWindow {
    property int indexOfMusic: 0
    id: root
    visible: true
    width: 400
    height: 480
    title: qsTr("Hello World")

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: playView
            model: playlistmodel
            Layout.fillHeight: true
            currentIndex: -1

            delegate: Rectangle {
                id: delegate
                width: root.width
                height: 40
                color: ListView.isCurrentItem ? "red" : "white"

                Text {
                    text: getMusicName(model.source)

                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked:  {
                        statebtn.text = "Pause"
                        root.indexOfMusic = index
                        startPlaying()
                    }
                }
            }
        }

        RowLayout {
            id: progressrow
            width: root.width
            Layout.margins: 5

            MySlider {
                id: progressbar
                from: 0
                Layout.fillWidth: true
                sliderColor: 'red'
                sliderHeight: 5
                sliderRadius: 5
            }




// put two text types instead of one becaise i get text bug when i call two functions to get time
            Text {
                text: getTextDuration(progressbar.value) + ' / '
            }

            Text {
                text: getTextDuration(playMusic.duration)
            }


        }

        RowLayout {
            id: controls
            width: root.width
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
                        if (playMusic.playbackState == Audio.PlayingState) {
                            playMusic.pause()
                            statebtn.text = 'Play'
                        } else {
                            startPlaying()
                            statebtn.text = 'Pause'
                        }
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
            if (playMusic.duration !== progressbar.to)
                progressbar.to = playMusic.duration

            if (progressbar.value === playMusic.duration && playMusic.source != "")
                playNext()

            progressbar.value = playMusic.position

            console.log(progressbar.value)
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

    function getMusicName(string) {
        return String(string).replace(/^.*[\\\/]/, '').replace(/.\w+$/, '')
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


    function startPlaying() {
        playMusic.source = playlistmodel.at(indexOfMusic )
        playMusic.play()
        playView.currentIndex = indexOfMusic
        progressbar.to = playMusic.duration
    }
}





