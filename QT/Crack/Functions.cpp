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


long Functions::getFileSize(string name) {
    ifstream fichier (name);
    int count = 0;
    string line;

    while ( !fichier.eof() ) {
        fichier >> line;
        ++count;
    }
    fichier.close();
    return count;
}

void Functions::launchDictionaryBruteForce() {
    /*if(m_hash != NULL) {
        string tmpHash = m_hash;
        FILE * file = fopen("database.txt", "r");
        cout << "aaaa " << tmpHash << endl;

        long numberOfLines =  getFileSize("database.txt");
        cout << "aaaa " << tmpHash << endl;

        int lineSize = 100;

        crypt_data localData;
        char * databaseArray = (char *)  malloc(sizeof(char) * lineSize * numberOfLines);

        long noOfLines = 0;
        if (file != NULL) {
            char * currentLine = (char *) malloc(lineSize);
            int i  = 0;
            while (fgets (currentLine, lineSize, file) != NULL) {
                strcpy(&databaseArray[i*lineSize], currentLine) ;
                i++;
            }
        } else {
            cout << "ERROR" << endl;
        }
        fclose(file);
        cout << "bbb" << databaseArray << endl;

        //#pragma omp parallel for private(localData)
        for (int i = 0; i < numberOfLines; i++) {
            cout << "ccc" << m_hash << endl;

            if(!m_find) {
                localData.initialized = 0;
                if (encryptAndCompareDictionary(databaseArray[i], localData)) {
                    cout << "trouve" << databaseArray[i] <<  endl;
                    m_password = (char *) malloc(lineSize);
                    strcpy(m_password, databaseArray[i]);
                    i = numberOfLines;
                    m_find = true;
                }
            } else {
                i = taille;
            }
        }

    } else {
        cerr << "Error password not found" << endl;
    }*/
}


bool Functions::encryptAndCompareDictionary(string passwordCandidate, crypt_data localData) const{
    /*if(passwordCandidate.c_str()[passwordCandidate.size()-1] == '\n') {
        passwordCandidate.erase(passwordCandidate.size()-1);
        cout << passwordCandidate << endl;
        return strcmp(crypt_r(passwordCandidate.c_str(), m_hash, &localData), m_hash) == 0;
    } else {*/
        //cout << crypt_r(passwordCandidate.c_str(), m_hash, &localData)  << endl;

        return strcmp(crypt_r(passwordCandidate.c_str(), m_hash, &localData), m_hash) == 0;
    //}
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
