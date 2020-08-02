#include <QRegExp>
#include "playlistmodel.h"
#include <random>

PlaylistModel::PlaylistModel(QObject *parent) : QAbstractListModel(parent)
{
    m_roleNames[SourceRole] = "source";
    m_roleNames[NameRole] = "name";
    fetchMusic(QDir(QStandardPaths::writableLocation(QStandardPaths::MusicLocation)), 0, 1);
    fetchMusic(QDir(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)), 0, 1);
    sortPlaylist();
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

QUrl PlaylistModel::at(QJsonValue index) {
    return m_data.at(index.toInt())["url"];
}

void PlaylistModel::fetchMusic(QDir dir, int depthLevel, int maximumLevel) {
    if (depthLevel == maximumLevel)
        return;
    for (QString str : dir.entryList({"*.mp3"})) {
        QString file { "file:" + dir.filePath(str) };
        QHash<QString, QString> data { { "name", str }, { "url", file } };
        m_data.append(data);

    }

    for (const QString str : dir.entryList(QDir::Dirs)) {
        if (str == "." or str == "..")
            continue;
        fetchMusic(dir.filePath(str), depthLevel + 1, maximumLevel);
    }    
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
