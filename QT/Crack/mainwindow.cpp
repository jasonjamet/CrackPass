#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QPalette"
#include "QDialog"
#include "QTimer"
#include "QLCDNumber"
#include "QMessageBox"
#include <time.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_F(new Functions())
{
    QPalette palette;
    palette.setColor(QPalette::ButtonText,Qt::blue);
    palette.setColor(QPalette::Button,Qt::black);
    palette.setColor(QPalette::Window, Qt::gray);

    this->secondes = 0;



    ui->setupUi(this);

    setWindowTitle("CrackPassword");

    ui->ConfirmButton->setPalette(palette);
    ui->centralWidget->setPalette(palette);

    ui->QLCDtimer->display(secondes);

    ui->textPassword->setEnabled(false);


    map<string, string> userAndPass = m_F->readShadowFile("shadow");
    for (map<string ,string>::iterator it=userAndPass.begin(); it!=userAndPass.end(); ++it) {
        ui->comboBox->addItem(it->first.c_str());

    }

    QObject::connect(ui->StopButton, SIGNAL(clicked()),this, SLOT(SlotStop()));
    QObject::connect(this, SIGNAL(SignalStopLoad()), this, SLOT(SlotStop()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ConfirmButton_clicked()
{
    ui->label->setText("Hello <b>" +getUserName()+ "</b>, you just make crack password.");
    ui->label->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->ConfirmButton->setEnabled(false);
    ui->radioMPI->setEnabled(false);
    ui->radioOMPI->setEnabled(false);
    ui->radioOpenMP->setEnabled(false);
    ui->textPassword->setText("Searching password ...");


    //this->secondes = 0;
    //this->timer = new QTimer(this);
    //this->timer->start(1000);
    clock_t init, final;
    init=clock();

    if(ui->checkDico->isChecked())
    {
        cout << "CheckDico checked" << endl;
        if(ui->radioOMPI->isChecked())
        {
            cout << "Open / MPI Checked" << endl;
        }

        if(ui->radioMPI->isChecked())
        {
            cout << "MPI Checked" << endl;
        }

        if(ui->radioOpenMP->isChecked())
        {
            cout << "Openmp Checked" << endl;
        }
    }

    if(ui->checkBrute->isChecked())
    {
        cout << "CheckBrute checked" << endl;
        if(ui->radioOMPI->isChecked())
        {
            cout << "Open / MPI Checked" << endl;
        }

        if(ui->radioMPI->isChecked())
        {
            cout << "MPI Checked" << endl;
        }

        if(ui->radioOpenMP->isChecked())
        {
            cout << "Openmp Checked" << endl;
        }
    }




    time_t start = time(NULL);

    m_F->getPasswordEncryptedByName(m_F->readShadowFile("shadow"), getUserName().toLatin1().data());
    m_F->launchDictionaryBruteForce();
    time_t end = time(NULL);

    if (m_F->getFind() == true)
    {
        cout << "TRUE" << endl;
        cout << "Mot de passe trouvé :" << m_F->getPassword() << endl;

        ui->textPassword->setText(m_F->getPassword());

        emit SignalStopLoad();
    }



    this->secondes = (double)(end-start);
    ui->QLCDtimer->display(this->secondes);
}

QString MainWindow::getUserName()
{
   QString userName = ui->comboBox->currentText();

    return userName;
}


void MainWindow::tick()
{
    this->secondes++;
    ui->QLCDtimer->display(this->secondes);
}

void MainWindow::SlotTick()
{
    if (this->secondes == 0)
    {
        QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(tick()));

        m_F->getPasswordEncryptedByName(m_F->readShadowFile("shadow"), getUserName().toLatin1().data());
        m_F->launchDictionaryBruteForce();

    }
}

void MainWindow::SlotStop()
{
    //this->timer->stop();
    ui->comboBox->setEnabled(true);
    ui->ConfirmButton->setEnabled(true);
    ui->radioMPI->setEnabled(true);
    ui->radioOMPI->setEnabled(true);
    ui->radioOpenMP->setEnabled(true);


   // delete timer;
}
