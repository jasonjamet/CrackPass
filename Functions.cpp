//
// Created by etudiant on 06/10/15.
//

#include <string.h>
#include <crypt.h>
#include "Functions.h"

Functions::Functions(string salt, const char *hash) : m_salt(salt), m_hash(hash) {

}

void Functions::bruteForce(int max) {

    char *buf = (char *) malloc(max + 1);

    for (int i = 1; i <= max; ++i) {
        memset(buf, 0, max + 1);

        if (checkForce(buf, 0, i)) {
            printf("Trouve: %s\n", password);
            break;
        }

        printf("Tour: %d\n", i);
    }

    free(buf);
}

bool Functions::checkForce(char *str, int index, int max) {

    for (int i = 0; i < characters_size; ++i) {
        str[index] = characters[i];

        if (index == max - 1) {
            if (strcmp(str, m_hash) == 0) {
                password = str;
                return true;
            }
        } else {
            return checkForce(str, index + 1, max);
        }
    }

    return false;
}


bool Functions::encryptAndCompare(char *passwordEncrypted, const char * passwordCandidate) {

    char * passwordCandidateEncrypted = crypt(passwordCandidate, passwordEncrypted);

    if(strcmp(passwordEncrypted, passwordCandidateEncrypted) == 0) {
        return true;
    } else {
        return false;
    }
}