//
// Created by etudiant on 06/10/15.
//

#include "Functions.h"

Functions::Functions(const char *hash): m_hash(hash) {

}

void Functions::bruteForce(int max) {

    char *buf = (char *) malloc(max + 1);
    m_password = NULL;

    for (int i = 1; i <= max; ++i) {
        memset(buf, 0, max + 1);
        checkForce(buf, 0, i);

        if (m_password != NULL) {
            printf("Trouve: %s\n", m_password);
            break;
        }
    }

    free(buf);
}


void Functions::checkForce(char *str, int index, int max) {
    if (m_password == NULL) {
        for (int i = 0; i < characters_size; ++i) {
            str[index] = characters[i];
            if (index == max - 1) {
                if (encryptAndCompare(m_hash, str)) {
                    m_password = (char *) malloc(strlen(str));
                    strcpy(m_password, (const char *)str);
                    break;
                }
            } else {
                checkForce(str, index + 1, max);
            }
        }
    }
}


bool Functions::encryptAndCompare(const char *passwordEncrypted, const char * passwordCandidate) {
    char * passwordCandidateEncrypted = crypt(passwordCandidate, passwordEncrypted);
    return strcmp(passwordEncrypted, passwordCandidateEncrypted) == 0;
}