//
// Created by etudiant on 06/10/15.
//

#include "QT/Crack/Functions.h"

int main(int argc, char *argv[]) {


    Functions *F = new Functions();
    //F->lauchSimpleBruteForce(F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason"), 4);
    F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason");
    F->launchDictionaryBruteForce();
    //F->launchSimpleBruteForce(3);
    delete (F);

    //launchParallelBF(3);


    return 0;
}

