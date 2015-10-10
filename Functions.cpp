
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



void Functions::readFile() {

    const int SIZE = 100;

    FILE * database = NULL;
    database = fopen("database.txt", "r");

    char * line = (char*) malloc(SIZE);

    while (fgets(line, SIZE, database) != NULL) {

        if (encryptAndCompare(line)) {
            strcpy(m_password, line);
            break;
        }

    }

    fclose(database);
}


bool Functions::encryptAndCompare(const char * passwordCandidate) const{
    return strcmp(m_hash, crypt(passwordCandidate, m_hash)) == 0;
}

char * Functions::getPassword() const {
    return m_password;
}