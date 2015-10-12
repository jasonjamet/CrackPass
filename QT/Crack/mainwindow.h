#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "research.h"

#include "Functions.h"
#include <time.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString getUserName();

public slots:
    void SlotTick();
    void tick();
    void SlotStop();
    void on_ConfirmButton_clicked();

private:
    Ui::MainWindow *ui;
    Research *research;

    QTimer *timer;
    int secondes;
    Functions * m_F;


};

#endif // MAINWINDOW_H
