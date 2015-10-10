#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "research.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool LoadFile(QString File);

private slots:
    void on_pushButton1_clicked();

private:
    Ui::MainWindow *ui;
    Research *research;
};

#endif // MAINWINDOW_H
