import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: root
    property int from
    property int to
    property int value
    property int sliderHeight;
    property int sliderRadius;
    property string sliderColor;

    Rectangle {
        id: progressbar_background
        property bool clicked: false
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: sliderHeight
        radius: sliderRadius
        color: Qt.lighter(sliderColor)

        MouseArea {
            anchors.fill: parent
            onPositionChanged: {
                if (!progressbar.to)
                    return
                if (progressbar_background.clicked) {
                    if (mouseX >= 0 && mouseX <= parent.width) {
                        progressbar.value = Math.trunc(progressbar.to / width * mouseX)
                    }
                }
            }

            onClicked: {
                if (!progressbar.to)
                    return
                progressbar_background.clicked = true
            }
            onReleased: {
                if (!progressbar.to)
                    return
                playMusic.seek(Math.trunc(progressbar.to / width * mouseX))
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
}
