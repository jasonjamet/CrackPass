#include "Functions.h"
#include <omp.h>
Functions::Functions(): m_hash(NULL), m_password(NULL), m_find(false) {

}

Functions::~Functions() {
}
struct crypt_data data;

map<string, string> Functions::readShadowFile(string shadowFileName) {
    map<string, string> userAndPass;

    ifstream shadowFileStream;
    shadowFileStream.open(shadowFileName);
    if (shadowFileStream.is_open()) {
        string line;
        while (getline(shadowFileStream, line)) {
            char *token = strtok(strdup(line.c_str()), ":");

            char * userPass = strtok(NULL, ":");
            if(strcmp(userPass, "*") && strcmp(userPass, "!") != 0) {
                userAndPass[token] = userPass;
            }
            strtok(NULL, ":");

        }
        shadowFileStream.close();

    } else {
        cerr << "Error during file opening" << endl;
    }
    return userAndPass;
}

const char *Functions::getPasswordEncryptedByName(map<string, string> userAndPass, string userName) {
    if (!userAndPass.empty() && userAndPass.count(userName) == 1) {
        m_hash = userAndPass[userName].c_str();
        return m_hash;
    } else {
        cerr << "Error name not found, or multiple name" << endl;
        return NULL;
    }
}

void Functions::launchSimpleBruteForce(int LongueurMax) {
    for (int longueur=1; longueur <= LongueurMax; longueur++) {
        checkForce(longueur, 'a', 'z');
    }
}


void Functions::checkForce(int longueur, char begin, char end) {

    char code[255]; // tableau contenant le code
    int i;

    #pragma omp parallel for\
    schedule(dynamic) default(shared)
    for (int i=0; i < longueur; i++) {
        code[i] = begin;
    }

    code[longueur] = 0;

    //#pragma omp parallel

    /*#pragma omp parallel for\
    schedule(dynamic) default(shared)*/


    //#pragma omp parallel
    /*while(code[longueur-1] < end) {
        if (!m_find) {
            i = 0;
            //#pragma omp parallel
            while (code[i] > end && code[i + 1] != 0) {
                code[i] = begin;
                code[++i]++;

                //cout << omp_get_thread_num() << endl;
            }

            data.initialized = 0;
            if (encryptAndCompare(code)) {
                cout << code << endl;
                m_password = (char *) malloc(strlen(code));
                strcpy(m_password, code);
                m_find = true;
            }

            code[0]++;
        } else {
            code[longueur-1] = end;
        }
    }*/
}

void Functions::launchDictionaryBruteForce() {
    if(m_hash != NULL) {
        const int SIZE = 100;
        FILE * database = NULL;
        database = fopen("database.txt", "r");


        long lSize;
        fseek (database , 0 , SEEK_END);
        lSize = ftell (database);
        rewind (database);
        cout << lSize << endl;

        char * line = (char*) malloc(SIZE);


        #pragma omp parallel for private(data)
        for (int i = 0; i < lSize; i++) {
            if(!m_find) {
                data.initialized = 0;

                string lineCpy = fgets(line, SIZE, database);

                if (encryptAndCompareDictionary(lineCpy)) {
                    cout << lineCpy << endl;
                    m_password = (char *) malloc(lineCpy.size());
                    strcpy(m_password, lineCpy.c_str());
                    i = lSize;
                    m_find = true;
                }
            } else {
                i = lSize;
            }
        }
        fclose(database);

    } else {
        cerr << "Error password not found" << endl;
    }
}


bool Functions::encryptAndCompareDictionary(string passwordCandidate) const{
    return strcmp(crypt_r(strtok((char *) passwordCandidate.c_str(), "\n"), m_hash, &data), m_hash) == 0;
}

bool Functions::encryptAndCompare(char * passwordCandidate) const{
    return strcmp(crypt_r(passwordCandidate, m_hash, &data), m_hash) == 0;
}

char * Functions::getPassword() const {
    return m_password;
}

bool Functions::getFind() const {
    return m_find;
}
