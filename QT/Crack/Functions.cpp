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


void Functions::bruteImpl(char* str, int index, int maxDepth, crypt_data localData) {
    for (int i = 0; i < characters_size; ++i) {
        localData.initialized = 0;

        str[index] = characters[i];
        if (index == maxDepth - 1) {

            cout << str << endl;
           if (encryptAndCompare(str, localData)) {
                m_find = true;

                cout << "TROUVE: " << str << endl;
                m_password = (char *) malloc(strlen(str));
                strcpy(m_password, str);
                i = characters_size;
            }
        }
        else {
            bruteImpl(str, index + 1, maxDepth, localData);
        }
    }
}

void Functions::bruteSequential(char x, int maxLen) {
    crypt_data localData;
    char* buf = (char *) malloc(maxLen + 1);

    buf[0] = x;
    #pragma omp parallel for private(localData)
    for (int i = 2; i <= maxLen; ++i) {
        if (!m_find) {
            buf[i]='\0';
            bruteImpl(buf, 1, i, localData);
        } else {
            i = maxLen+1;
        }
    }

    free(buf);
}

void Functions::launchSimpleBruteForce(int max) {
#pragma omp parallel for
    for (int k = 0; k < characters_size; k++) {
        if (!m_find) {
            bruteSequential(characters[k], max);
        } else {
            k = characters_size;
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
    return strcmp(crypt_r(strtok((char *) passwordCandidate.c_str(), "\n"), m_hash, &localData), m_hash) == 0;
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

void Functions::initialize()
{
    m_hash = NULL;
    m_find = false;
}
}
