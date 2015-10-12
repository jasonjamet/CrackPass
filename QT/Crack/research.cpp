#include "research.h"
#include "ui_research.h"
#include "mainwindow.h"

#include "Functions.h"

Research::Research(QString userName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Research)
{
    ui->setupUi(this);

    setWindowTitle("CrackPassword");

    ui->label->setText("You can see the password's "+userName+ " here :");

}

Research::~Research()
{
    delete ui;
}


