#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QPalette"
#include "QDialog"
#include "QTimer"
#include "QLCDNumber"
#include "QMessageBox"

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


   // QObject::connect(ui->ConfirmButton, SIGNAL(clicked()),this, SLOT(SlotTick()));
    QObject::connect(ui->StopButton, SIGNAL(clicked()),this, SLOT(SlotStop()));

    //F->lauchSimpleBruteForce(F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason"), 4);


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


    m_F->lauchDictionaryBruteForce(m_F->getPasswordEncryptedByName(m_F->readShadowFile("shadow"), getUserName().toLatin1().data()));


    if (m_F->getFind() == true)
    {
        cout << "TRUE" << endl;
        cout << "Mot de passe trouvé :" << m_F->getPassword() << endl;

        ui->textPassword->setText(m_F->getPassword());
    }

    final=clock()-init;
    this->secondes = (double)final / ((double)CLOCKS_PER_SEC);
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
        m_F->lauchDictionaryBruteForce(m_F->getPasswordEncryptedByName(m_F->readShadowFile("shadow"), getUserName().toLatin1().data()));


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





