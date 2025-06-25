#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "servermanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ServerManager *serverManager;

private slots:
    void onPlayerCountChanged(int count);
    void onLogMessage(QString msg);
};
#endif // MAINWINDOW_H
