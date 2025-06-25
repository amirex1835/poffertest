#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), socket(new QTcpSocket(this)) {
    setupUI();

    connect(connectBtn, &QPushButton::clicked, this, &MainWindow::connectToServer);
    connect(sendBtn, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
    connect(socket, &QTcpSocket::connected, this, [=]() {
        log("✅ Connected to server.");
        sendBtn->setEnabled(true);
    });
    connect(socket, &QTcpSocket::disconnected, this, [=]() {
        log("⚠️ Disconnected from server.");
        sendBtn->setEnabled(false);
    });
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    ipEdit = new QLineEdit(this);
    ipEdit->setPlaceholderText("Enter server IP");
    connectBtn = new QPushButton("Connect", this);
    sendBtn = new QPushButton("Send", this);
    sendBtn->setEnabled(false);

    logBox = new QTextEdit(this);
    logBox->setReadOnly(true);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(ipEdit);
    topLayout->addWidget(connectBtn);
    topLayout->addWidget(sendBtn);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addLayout(topLayout);
    layout->addWidget(logBox);

    resize(500, 300);
    setWindowTitle("Client");
}

void MainWindow::log(const QString &message) {
    logBox->append(message);
}

void MainWindow::connectToServer() {
    QString ip = ipEdit->text().trimmed();
    socket->connectToHost(QHostAddress(ip), 1234);
    log("🔄 Connecting to " + ip);
}

void MainWindow::sendMessage() {
    socket->write("سلام از کلاینت!");
    log("📤 Sent: سلام از کلاینت!");
}

void MainWindow::onReadyRead() {
    QByteArray data = socket->readAll();
    log("📥 Received: " + QString::fromUtf8(data));
}
