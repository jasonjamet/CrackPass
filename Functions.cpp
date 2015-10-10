
#include "Functions.h"
//#include "mpi.h"

Functions::Functions(const char * hash): m_hash(hash), m_password(NULL), m_find(false) {

}

Functions::~Functions() {
    delete m_password;
}


void Functions::bruteForce(int max) {

    char *buf = (char *) malloc(max + 1);
    int i;
    
    #pragma omp master
    for (i = 1; i <= max; ++i) {

        if (!m_find) {
           break;
        }
    }

    free(buf);
}


void Functions::checkForce(char * str, int index, int max) {

    int i;

    #pragma omp parallel for \
    default(shared) private(i) schedule(dynamic)
    for (i = 0; i < characters_size; ++i) {
        if (!m_find) {
            str[index] = characters[i];
            if (index == max - 1) {

                char passwordCandidate[strlen(str)];
                strcpy(passwordCandidate, str);

                cout << str << endl;

                if (encryptAndCompare(passwordCandidate)) {
                    m_find = true;
                    m_password = (char *) malloc(strlen(passwordCandidate));
                    strcpy(m_password, passwordCandidate);
                    #pragma omp flush (m_find)
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