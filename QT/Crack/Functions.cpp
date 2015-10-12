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

void Functions::launchSimpleBruteForce(int max) {

    char *buf = (char *) malloc(max + 1);

    for (int i = 1; i <= 2; ++i) {
        memset(buf, 0, max + 1);
        checkForce(buf, 0, i-1);
    }

    free(buf);
}

void Functions::checkForce(char * str, int index, int max) {
    #pragma omp parallele for\
    schedule(dynamic, 32)
    for (int i = 0; i < characters_size; ++i) {
        str[index] = characters[i];

        if (index < max)
            checkForce(str, index + 1, max);

        cout << str << endl;
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
