#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QPalette"
#include "../../Functions.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPalette palette;
    palette.setColor(QPalette::ButtonText,Qt::blue);
    palette.setColor(QPalette::Button,Qt::black);
    palette.setColor(QPalette::Window, Qt::gray);

    ui->setupUi(this);

    setWindowTitle("CrackPassword");

    ui->pushButton1->setPalette(palette);
    ui->centralWidget->setPalette(palette);


    Functions *F = new Functions();
    map<string, string> userAndPass = F->readShadowFile("shadow");
    for (map<string ,string>::iterator it=userAndPass.begin(); it!=userAndPass.end(); ++it) {
        ui->comboBox->addItem(it->first.c_str());
    }
    //F->lauchSimpleBruteForce(F->getPasswordEncryptedByName(, "jason"), 4);
    delete (F);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton1_clicked()
{
    research = new Research(this);
    research->show();
}
