#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>

class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();

private:
    void setupUI();
    void log(const QString &message);

    QTcpServer *server;
    QTcpSocket *clientSocket;
    QTextEdit *logBox;
};

#endif // MAINWINDOW_H
