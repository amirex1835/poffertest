#include "servermanager.h"

ServerManager::ServerManager(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &ServerManager::onNewConnection);
}

bool ServerManager::startServer(quint16 port)
{
    if (server->listen(QHostAddress::Any, port)) {
        emit logMessage("✅ Listening on port " + QString::number(port));
        return true;
    } else {
        emit logMessage("❌ Failed to start server.");
        return false;
    }
}

void ServerManager::onNewConnection()
{
    while (server->hasPendingConnections()) {
        QTcpSocket *client = server->nextPendingConnection();
        if (clients.size() >= 4) {
            client->disconnectFromHost();
            emit logMessage("🚫 More than 4 players — rejected.");
            continue;
        }

        clients.append(client);
        emit logMessage("✅ Player connected. Total: " + QString::number(clients.size()));
        emit playerCountChanged(clients.size());

        connect(client, &QTcpSocket::readyRead, this, &ServerManager::onReadyRead);
        connect(client, &QTcpSocket::disconnected, this, &ServerManager::onClientDisconnected);
    }
}

void ServerManager::onClientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    clients.removeAll(client);
    client->deleteLater();
    emit logMessage("❗ Player disconnected. Total: " + QString::number(clients.size()));
    emit playerCountChanged(clients.size());
}

void ServerManager::onReadyRead()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = client->readAll();
    emit logMessage("📩 Message received: " + QString::fromUtf8(data));
    // TODO: handle incoming message
}
