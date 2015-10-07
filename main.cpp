//
// Created by etudiant on 06/10/15.
//

#include "Functions.h"


char *mdp = "aaaa";


int main() {

    Functions *F = new Functions("salt", mdp);

    F->bruteForce(4);

    delete (F);

    return 0;
}