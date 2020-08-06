#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QtGui>

class PlaylistModel : public QAbstractListModel
{
Q_OBJECT
public:
    explicit PlaylistModel(QObject *parent = nullptr);
    ~PlaylistModel();

    enum RoleNames {
        SourceRole = Qt::UserRole,
        NameRole = Qt::UserRole + 1
    };

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    void fetchMusic(QDir dir, int depthLevel, int maximumlevel);
    void sortPlaylist();
    Q_INVOKABLE void shufflePlaylist();
    Q_INVOKABLE QUrl urlAt(QJsonValue index);
    Q_INVOKABLE QString nameAt(QJsonValue index);

protected:
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QHash<int, QByteArray> m_roleNames;
    QList<QHash<QString, QString>> m_data;

};

#endif // PLAYLISTMODEL_H
