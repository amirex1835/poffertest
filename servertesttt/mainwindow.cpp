#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serverManager = new ServerManager(this);

    connect(ui->btnStartServer, &QPushButton::clicked, this, [=]() {
        if (serverManager->startServer(1234)) {
            ui->txtLog->append("✅ سرور راه‌اندازی شد.");
        } else {
            ui->txtLog->append("❌ خطا در راه‌اندازی سرور.");
        }
    });

    connect(serverManager, &ServerManager::playerCountChanged, this, &MainWindow::onPlayerCountChanged);
    connect(serverManager, &ServerManager::logMessage, this, &MainWindow::onLogMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPlayerCountChanged(int count)
{
    ui->lblPlayerCount->setText("Players Connected: " + QString::number(count));
}

void MainWindow::onLogMessage(QString msg)
{
    ui->txtLog->append(msg);
}
