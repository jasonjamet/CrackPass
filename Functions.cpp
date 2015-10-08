
#include "Functions.h"

Functions::Functions(const char * hash): m_hash(hash), m_password(NULL) {

}

Functions::~Functions() {
    delete m_password;
}


void Functions::bruteForce(int max) {

    char *buf = (char *) malloc(max + 1);

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
                if (encryptAndCompare(str)) {
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


bool Functions::encryptAndCompare(const char * passwordCandidate) {
    return strcmp(m_hash, crypt(passwordCandidate, m_hash)) == 0;
}