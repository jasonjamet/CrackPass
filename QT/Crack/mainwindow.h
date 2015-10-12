#ifndef MAINWINDOW_H$6$KzWGv3OY$1LNpaPmbH5GOD7D.iY54XDEBtR0c06uE4RQ6GLpiPfSPbKP2IFY6XtLeFybJnelQCqLF010Zdm3PTSUoistds0
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_pushButton1_clicked();

private:
    Ui::MainWindow *ui;
    Research *research;
};

#endif // MAINWINDOW_H
