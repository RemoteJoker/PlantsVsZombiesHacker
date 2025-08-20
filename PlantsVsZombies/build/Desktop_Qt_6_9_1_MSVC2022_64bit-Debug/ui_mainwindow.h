/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *InjectAction;
    QAction *UnloadAction;
    QWidget *centralwidget;
    QPushButton *FunBtn_00;
    QPushButton *FunBtn_01;
    QPushButton *FunBtn_02;
    QPushButton *FunBtn_03;
    QPushButton *FunBtn_04;
    QPushButton *FunBtn_05;
    QPushButton *FunBtn_06;
    QPushButton *FunBtn_07;
    QPushButton *FunBtn_08;
    QMenuBar *Menu;
    QMenu *StartMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 400);
        InjectAction = new QAction(MainWindow);
        InjectAction->setObjectName("InjectAction");
        UnloadAction = new QAction(MainWindow);
        UnloadAction->setObjectName("UnloadAction");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        FunBtn_00 = new QPushButton(centralwidget);
        FunBtn_00->setObjectName("FunBtn_00");
        FunBtn_00->setGeometry(QRect(20, 10, 100, 30));
        FunBtn_00->setStyleSheet(QString::fromUtf8("font:20px;\n"
"font-family:songti;"));
        FunBtn_01 = new QPushButton(centralwidget);
        FunBtn_01->setObjectName("FunBtn_01");
        FunBtn_01->setGeometry(QRect(20, 50, 100, 30));
        FunBtn_01->setStyleSheet(QString::fromUtf8("font:20px;\n"
"font-family:songti;"));
        FunBtn_02 = new QPushButton(centralwidget);
        FunBtn_02->setObjectName("FunBtn_02");
        FunBtn_02->setGeometry(QRect(20, 90, 100, 30));
        FunBtn_02->setStyleSheet(QString::fromUtf8("font:20px;\n"
"font-family:songti;"));
        FunBtn_03 = new QPushButton(centralwidget);
        FunBtn_03->setObjectName("FunBtn_03");
        FunBtn_03->setGeometry(QRect(20, 130, 100, 30));
        FunBtn_03->setStyleSheet(QString::fromUtf8("font:20px;\n"
"font-family:songti;"));
        FunBtn_04 = new QPushButton(centralwidget);
        FunBtn_04->setObjectName("FunBtn_04");
        FunBtn_04->setGeometry(QRect(20, 170, 100, 30));
        FunBtn_04->setStyleSheet(QString::fromUtf8("font:20px;\n"
"font-family:songti;"));
        FunBtn_05 = new QPushButton(centralwidget);
        FunBtn_05->setObjectName("FunBtn_05");
        FunBtn_05->setGeometry(QRect(20, 210, 100, 30));
        FunBtn_05->setStyleSheet(QString::fromUtf8("font:20px;\n"
"font-family:songti;"));
        FunBtn_06 = new QPushButton(centralwidget);
        FunBtn_06->setObjectName("FunBtn_06");
        FunBtn_06->setGeometry(QRect(20, 250, 100, 30));
        FunBtn_06->setStyleSheet(QString::fromUtf8("font:20px;\n"
"font-family:songti;"));
        FunBtn_07 = new QPushButton(centralwidget);
        FunBtn_07->setObjectName("FunBtn_07");
        FunBtn_07->setGeometry(QRect(20, 290, 100, 30));
        FunBtn_07->setStyleSheet(QString::fromUtf8("font:20px;\n"
"font-family:songti;"));
        FunBtn_08 = new QPushButton(centralwidget);
        FunBtn_08->setObjectName("FunBtn_08");
        FunBtn_08->setGeometry(QRect(20, 330, 100, 30));
        FunBtn_08->setStyleSheet(QString::fromUtf8("font:20px;\n"
"font-family:songti;"));
        MainWindow->setCentralWidget(centralwidget);
        Menu = new QMenuBar(MainWindow);
        Menu->setObjectName("Menu");
        Menu->setGeometry(QRect(0, 0, 600, 21));
        StartMenu = new QMenu(Menu);
        StartMenu->setObjectName("StartMenu");
        MainWindow->setMenuBar(Menu);

        Menu->addAction(StartMenu->menuAction());
        StartMenu->addAction(InjectAction);
        StartMenu->addAction(UnloadAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        InjectAction->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\205\245", nullptr));
        UnloadAction->setText(QCoreApplication::translate("MainWindow", "\345\215\270\350\275\275", nullptr));
        FunBtn_00->setText(QCoreApplication::translate("MainWindow", "\346\227\240\351\231\220\351\230\263\345\205\211", nullptr));
        FunBtn_01->setText(QCoreApplication::translate("MainWindow", "\345\215\241\346\247\275\345\206\267\345\215\264", nullptr));
        FunBtn_02->setText(QCoreApplication::translate("MainWindow", "\346\231\272\346\205\247\346\240\221", nullptr));
        FunBtn_03->setText(QCoreApplication::translate("MainWindow", "\346\227\240\351\231\220\351\207\221\345\270\201", nullptr));
        FunBtn_04->setText(QCoreApplication::translate("MainWindow", "\347\247\222\346\235\200\345\215\232\345\243\253", nullptr));
        FunBtn_05->setText(QCoreApplication::translate("MainWindow", "\345\205\250\345\261\217\350\275\260\347\202\270", nullptr));
        FunBtn_06->setText(QCoreApplication::translate("MainWindow", "\346\244\215\347\211\251\346\227\240\346\225\214", nullptr));
        FunBtn_07->setText(QCoreApplication::translate("MainWindow", "\345\203\265\345\260\270\346\227\240\346\225\214", nullptr));
        FunBtn_08->setText(QCoreApplication::translate("MainWindow", "\347\275\220\345\255\220\351\200\217\350\247\206", nullptr));
        StartMenu->setTitle(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
