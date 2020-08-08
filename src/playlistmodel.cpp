#include <QRegExp>
#include <random>

#include "playlistmodel.h"

#ifdef Q_OS_ANDROID
#include <QtAndroid>

void permissionCallback(const QtAndroid::PermissionResultMap &res) {
    if (res["android.permission.READ_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied)
        QGuiApplication::exit();
//    else
//        PlaylistModel::instance()->fetchMusic();
}

#endif

PlaylistModel *PlaylistModel::m_instance = nullptr;

PlaylistModel::PlaylistModel(QObject *parent) : QAbstractListModel(parent)
{
    m_instance = this;

    m_roleNames[SourceRole] = "source";
    m_roleNames[NameRole] = "name";

#ifdef Q_OS_ANDROID
   QtAndroid::requestPermissions({QString("android.permission.READ_EXTERNAL_STORAGE")}, permissionCallback);

   while (QtAndroid::checkPermission("android.permission.READ_EXTERNAL_STORAGE") != QtAndroid::PermissionResult::Granted) {
       QThread::sleep(1);
   }
#endif
    fetchMusic();


    sortPlaylist();
}

void PlaylistModel::fetchMusic() {
    QList<QDir> dirs = {QDir(QStandardPaths::writableLocation(QStandardPaths::MusicLocation)), QDir(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation))};

    for (QDir dir : dirs) {
        for (QString str : dir.entryList({"*.mp3", "*.wav"})) {
            QString file { "file:" + dir.filePath(str) };
            QHash<QString, QString> data { { "name", str }, { "url", file } };
            m_data.append(data);
        }
    }
}

void PlaylistModel::shufflePlaylist() {
    emit layoutAboutToBeChanged();
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_data.begin(), m_data.end(), g);
    emit layoutChanged();
}

void PlaylistModel::sortPlaylist() {
    std::sort(m_data.begin(), m_data.end(), [](const QHash<QString, QString> &first, const QHash<QString, QString> &second) -> bool {
        return first["name"].toLower()[0] < second["name"].toLower()[0];
    });
}

QUrl PlaylistModel::urlAt(QJsonValue index) {
    return m_data.at(index.toInt())["url"];
}

QString PlaylistModel::nameAt(QJsonValue index) {
    return m_data.at(index.toInt())["name"];
}

PlaylistModel::~PlaylistModel() {

}

int PlaylistModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    switch(role) {
    case SourceRole:
        return m_data.at(row)["url"];
    case NameRole:
        return m_data.at(row)["name"];
    }
    return QVariant();
}

QHash<int, QByteArray> PlaylistModel::roleNames() const {
    return m_roleNames;
}
