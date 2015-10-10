#include "research.h"
#include "ui_research.h"

Research::Research(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Research)
{
    ui->setupUi(this);

    setWindowTitle("CrackPassword");

}

Research::~Research()
{
    delete ui;
}
