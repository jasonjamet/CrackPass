#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QPalette"

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

    if(!LoadFile("/home/etudiant/file.txt"))
    {
        ui->comboBox->addItem("Error during opening file");
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::LoadFile(QString FileName)
{
    QFile file(FileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))return false;
        else
        {
            while (!file.atEnd())
            {
                QString line = file.readLine();
                ui->comboBox->addItem(line);
            }
            return true;
        }

        file.close();
}

void MainWindow::on_pushButton1_clicked()
{
    research = new Research(this);
    research->show();
}
