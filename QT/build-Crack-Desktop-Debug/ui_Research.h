/********************************************************************************
** Form generated from reading UI file 'Research.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESEARCH_H
#define UI_RESEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Research
{
public:
    QWidget *centralwidget;
    QListWidget *listWidget;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Research)
    {
        if (Research->objectName().isEmpty())
            Research->setObjectName(QStringLiteral("Research"));
        Research->resize(800, 600);
        centralwidget = new QWidget(Research);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(120, 140, 256, 192));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 50, 201, 16));
        Research->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Research);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        Research->setMenuBar(menubar);
        statusbar = new QStatusBar(Research);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Research->setStatusBar(statusbar);

        retranslateUi(Research);

        QMetaObject::connectSlotsByName(Research);
    } // setupUi

    void retranslateUi(QMainWindow *Research)
    {
        Research->setWindowTitle(QApplication::translate("Research", "MainWindow", 0));
        label->setText(QApplication::translate("Research", "You can see here your password", 0));
    } // retranslateUi

};

namespace Ui {
    class Research: public Ui_Research {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESEARCH_H
