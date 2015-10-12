#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QPalette"
#include "QDialog"
#include "QTimer"
#include "QLCDNumber"
#include "QMessageBox"

#include "Functions.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPalette palette;
    palette.setColor(QPalette::ButtonText,Qt::blue);
    palette.setColor(QPalette::Button,Qt::black);
    palette.setColor(QPalette::Window, Qt::gray);

    this->secondes = 0;



    ui->setupUi(this);

    setWindowTitle("CrackPassword");

    ui->pushButton1->setPalette(palette);
    ui->centralWidget->setPalette(palette);

    ui->QLCDtimer->display(secondes);

    Functions *F = new Functions();
    map<string, string> userAndPass = F->readShadowFile("../shadow");
    for (map<string ,string>::iterator it=userAndPass.begin(); it!=userAndPass.end(); ++it) {
        ui->comboBox->addItem(it->first.c_str());

    }

    delete (F);

    QObject::connect(ui->pushButton1, SIGNAL(clicked()),this, SLOT(SlotTick()));
    QObject::connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(SlotStop()));

    //F->lauchSimpleBruteForce(F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason"), 4);
    F->lauchDictionaryBruteForce(F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason"));

    delete (F);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getUserName()
{
   QString userName = ui->comboBox->currentText();

    return userName;
}

void MainWindow::on_pushButton1_clicked()
{
      ui->label->setText("Hello <b>" +getUserName()+ "</b>, you just make crack password.");
      ui->label->setEnabled(false);
      ui->comboBox->setEnabled(false);
      ui->pushButton1->setEnabled(false);

      this->secondes = 0;
      this->timer = new QTimer(this);

      this->timer->start(1000);

//    research = new Research(getUserName());
//    research->show();
}


void MainWindow::tick()
{
    this->secondes++;
    ui->QLCDtimer->display(this->secondes);
}

void MainWindow::SlotTick()
{
    if (this->secondes == 0)
        QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(tick()));
}

void MainWindow::SlotStop()
{
    this->timer->stop();
    ui->comboBox->setEnabled(true);
    ui->pushButton1->setEnabled(true);

    delete timer;
}



