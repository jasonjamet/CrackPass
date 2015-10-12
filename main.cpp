//
// Created by etudiant on 06/10/15.
//

#include "Functions.h"



int main(int argc, char *argv[]) {


    Functions *F = new Functions();
    //F->lauchSimpleBruteForce(F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason"), 4);
    F->lauchDictionaryBruteForce(F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason"));
    delete (F);
    return 0;
}

