//
// Created by etudiant on 06/10/15.
//

#include "QT/Crack/Functions.h"



int main(int argc, char *argv[]) {


    Functions *F = new Functions();
    F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason");
    F->launchDictionaryBruteForce();
    //F->launchSimpleBruteForce(3);
    delete (F);


    return 0;
}

