/********************************************************************************
** Form generated from reading UI file 'research.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESEARCH_H
#define UI_RESEARCH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Research
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Research)
    {
        if (Research->objectName().isEmpty())
            Research->setObjectName(QString::fromUtf8("Research"));
        Research->resize(800, 600);
        centralwidget = new QWidget(Research);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 90, 221, 16));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(100, 180, 256, 192));
        Research->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Research);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        Research->setMenuBar(menubar);
        statusbar = new QStatusBar(Research);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Research->setStatusBar(statusbar);

        retranslateUi(Research);

        QMetaObject::connectSlotsByName(Research);
    } // setupUi

    void retranslateUi(QMainWindow *Research)
    {
        Research->setWindowTitle(QApplication::translate("Research", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Research", "You can see your password here", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Research: public Ui_Research {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESEARCH_H
