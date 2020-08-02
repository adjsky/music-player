import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtMultimedia 5.15
import PlaylistModel 1.0


ApplicationWindow {
    property int indexOfMusic: 0
    id: root
    visible: true
    title: qsTr("Music Player")
    width: 500
    height: 500
    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width

    Interface {

    }
}
