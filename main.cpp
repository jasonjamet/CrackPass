//
// Created by etudiant on 06/10/15.
//

#include "Functions.h"
//#include "QT/Crack/mainwindow.h"
//#include <QApplication>



int main(int argc, char *argv[]) {
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();
    Functions *F = new Functions();
    F->lauchSimpleBruteForce(F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason"), 4);
    delete (F);
    return 0;
}
