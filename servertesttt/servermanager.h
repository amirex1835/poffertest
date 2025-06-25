#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class ServerManager : public QObject
{
    Q_OBJECT
public:
    explicit ServerManager(QObject *parent = nullptr);
    bool startServer(quint16 port = 1234);

signals:
    void playerCountChanged(int count);
    void logMessage(QString msg);

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();

private:
    QTcpServer *server;
    QVector<QTcpSocket*> clients;
};

#endif // SERVERMANAGER_H
