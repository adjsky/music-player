import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: root
    property int from
    property int to: getMusicDuration()
    property int value
    property int sliderHeight;
    property int sliderRadius;
    property string sliderColor;

    Rectangle {
        id: progressbar_background
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: sliderHeight
        radius: sliderRadius
        color: Qt.lighter(sliderColor)

        MouseArea {
            anchors.fill: parent
            onPositionChanged: {
                if (!root.to)
                    return
                if (mouseX >= 0 && mouseX <= parent.width) {
                    root.value = Math.trunc(root.to / width * mouseX)
                }
            }

            onClicked: {
                if (!root.to)
                    return
                root.value = Math.trunc(root.to / width * mouseX)
                playMusic.seek(root.value)
            }

            onReleased: {
                if (!root.to)
                    return
                playMusic.seek(root.value)
            }
        }
    }

    Rectangle {
        id: progressbar_drag
        anchors.verticalCenter: parent.verticalCenter
        width: (root.value / root.to) * root.width
        height: sliderHeight
        radius: sliderRadius
        color: sliderColor
    }

    function getMusicDuration() {
        if (playMusic.duration === 0)
            return 1
        return playMusic.duration
    }
}
