//
// Created by etudiant on 06/10/15.
//

#include <vector>
#include "QT/Crack/Functions.h"

int main(int argc, char *argv[]) {

    Functions * F = new Functions();

    F->setPasswordEncryptedByName(F->readShadowFile("shadow"), "jason");
    F->launchDictionaryBruteForce();

    if (F->getFind()) {
        cout << "Password found: " << F->getPassword() << endl;
    } else {
        cout << "Password not found !" << endl;
    }

    return 0;
}

