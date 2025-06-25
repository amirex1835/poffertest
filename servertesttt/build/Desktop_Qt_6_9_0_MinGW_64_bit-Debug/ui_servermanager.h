/********************************************************************************
** Form generated from reading UI file 'servermanager.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERMANAGER_H
#define UI_SERVERMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerManager
{
public:

    void setupUi(QWidget *ServerManager)
    {
        if (ServerManager->objectName().isEmpty())
            ServerManager->setObjectName("ServerManager");
        ServerManager->resize(400, 300);

        retranslateUi(ServerManager);

        QMetaObject::connectSlotsByName(ServerManager);
    } // setupUi

    void retranslateUi(QWidget *ServerManager)
    {
        ServerManager->setWindowTitle(QCoreApplication::translate("ServerManager", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerManager: public Ui_ServerManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERMANAGER_H
