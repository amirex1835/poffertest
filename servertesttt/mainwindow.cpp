#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), server(new QTcpServer(this)), clientSocket(nullptr) {
    setupUI();

    connect(server, &QTcpServer::newConnection, this, &MainWindow::onNewConnection);

    if (server->listen(QHostAddress::Any, 1234)) {
        log("✅ Server started on port 1234.");
    } else {
        log("❌ Failed to start server.");
    }
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    logBox = new QTextEdit(this);
    logBox->setReadOnly(true);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(logBox);

    resize(400, 300);
    setWindowTitle("Server");
}

void MainWindow::log(const QString &message) {
    logBox->append(message);
}

void MainWindow::onNewConnection() {
    clientSocket = server->nextPendingConnection();
    log("🔌 Client connected.");

    connect(clientSocket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MainWindow::onClientDisconnected);
}

void MainWindow::onReadyRead() {
    QByteArray data = clientSocket->readAll();
    log("📥 Received: " + QString::fromUtf8(data));
    clientSocket->write("👋 سلام از سرور!");
}

void MainWindow::onClientDisconnected() {
    log("⚠️ Client disconnected.");
    clientSocket->deleteLater();
    clientSocket = nullptr;
}
