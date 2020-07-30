#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent) : QAbstractListModel(parent)
{
    m_roleNames[SourceRole] = "source";

    fetchMusic(QDir::homePath(), 0, 2);

}

QUrl PlaylistModel::at(QJsonValue index) {
    return m_urls.at(index.toInt());
}

void PlaylistModel::fetchMusic(QDir dir, int depthLevel, int maximumLevel) {
    if (depthLevel == maximumLevel)
        return;
    for (const QString str : dir.entryList({"*.mp3"})) {
        m_urls.append("file:" + dir.filePath(str));
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
    return m_urls.count();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    switch(role) {
    case SourceRole:
        return m_urls.at(row);
    }
    return QVariant();
}

QHash<int, QByteArray> PlaylistModel::roleNames() const {
    return m_roleNames;
}
