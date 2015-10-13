#include "Functions.h"
#include <omp.h>
Functions::Functions(): m_hash(NULL), m_password(NULL), m_find(false) {

}

Functions::~Functions() {
}

map<string, string> Functions::readShadowFile(string shadowFileName) {
    map<string, string> userAndPass;

    ifstream shadowFileStream;
    shadowFileStream.open(shadowFileName);
    if (shadowFileStream.is_open()) {
        string line;
        while (getline(shadowFileStream, line)) {
            char *token = strtok(strdup(line.c_str()), ":");
            if(token != NULL) {
                char * userPass = strtok(NULL, ":");
                if(userPass != NULL) {
                    if(strcmp(userPass, "*") && strcmp(userPass, "!") != 0) {
                        userAndPass[token] = userPass;
                    }
                    strtok(NULL, ":");
                }
            }
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
        //cout << m_hash << endl;
        return m_hash;
    } else {
        cerr << "Error name not found, or multiple name" << endl;
        return NULL;
    }
}

void Functions::launchSimpleBruteForce(int max) {

    char *buf = (char *) malloc(max + 1);
    crypt_data localData;

    for (int i = 1; i <= max; ++i) {

        if (!m_find) {
            memset(buf, 0, max + 1);
            checkForce(buf, 0, i - 1, localData);
        } else {
            break;
        }
    }

    free(buf);
}

void Functions::checkForce(char * str, int index, int max, crypt_data localData) {

    #pragma omp parallel for
    for (int i = 0; i < characters_size; ++i) {
        if(!m_find) {
            localData.initialized = 0;

            str[index] = characters[i];

            if (encryptAndCompareDictionary(str, localData)) {
                cout << "TROUVE: " << str << endl;
                m_password = (char *) malloc(strlen(str));
                strcpy(m_password, str);
                m_find = true;
            }

            if (index < max)
                checkForce(str, index + 1, max, localData);
        } else {
            i = characters_size;
        }
    }

}

void Functions::launchDictionaryBruteForce() {
    if(m_hash != NULL) {
        const int SIZE = 100;
        FILE * database = NULL;
        database = fopen("database.txt", "r");
        crypt_data localData;

        long lSize;
        fseek (database , 0 , SEEK_END);
        lSize = ftell (database);
        rewind (database);
        cout << lSize << endl;

        char * line = (char*) malloc(SIZE);


        #pragma omp parallel for\
        private(localData),schedule(dynamic, 32)
        for (int i = 0; i < lSize; i++) {
            if(!m_find) {
                localData.initialized = 0;

                string lineCpy = fgets(line, SIZE, database);
                if (encryptAndCompareDictionary(lineCpy, localData)) {
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


bool Functions::encryptAndCompareDictionary(string passwordCandidate, crypt_data localData) const{
    if(strcmp(passwordCandidate.c_str(), "\n") > 0) {
        passwordCandidate.erase(passwordCandidate.size()-2);
        cout << passwordCandidate << endl;
        return strcmp(crypt_r(passwordCandidate.c_str(), m_hash, &localData), m_hash) == 0;
    } else {
        return strcmp(crypt_r(passwordCandidate.c_str(), m_hash, &localData), m_hash) == 0;
    }
}

bool Functions::encryptAndCompare(char * passwordCandidate, crypt_data localData) const{
    return strcmp(crypt_r(passwordCandidate, m_hash, &localData), m_hash) == 0;
}

char * Functions::getPassword() const {
    return m_password;
}

bool Functions::getFind() const {
    return m_find;
}
