#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void connectToServer();
    void sendMessage();
    void onReadyRead();

private:
    void setupUI();
    void log(const QString &message);

    QLineEdit *ipEdit;
    QTextEdit *logBox;
    QPushButton *connectBtn;
    QPushButton *sendBtn;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
