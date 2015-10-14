#include "Functions.h"
#include <omp.h>
#include <vector>

Functions::Functions(): m_hash(""), m_password(""), m_find(false) {

}

Functions::~Functions() {
}

map<string, string> Functions::readShadowFile(string shadowFileName) const {

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

void Functions::setPasswordEncryptedByName(map<string, string> userAndPass, string userName) {
    if (!userAndPass.empty() && userAndPass.count(userName) == 1) {
        m_hash = userAndPass[userName];
    } else {
        cerr << "Error name not found, or multiple name" << endl;
    }
}


void Functions::bruteImpl(char* str, int index, int maxDepth, crypt_data & localData) {

    for (int i = 0; i < characters_size; ++i) {
        if(!m_find) {
            localData.initialized = 0;

            str[index] = characters[i];
            if (index == maxDepth - 1) {
                cout << str << endl;
                if (encryptAndCompare(str, localData)) {
                    m_find = true;
                    m_password = str;
                    i = characters_size;
                }
            }
            else {
                bruteImpl(str, index + 1, maxDepth, localData);
            }
        } else {
           i =  characters_size;
        }

    }
}

void Functions::bruteSequential(char x, int maxLen)  {
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
    if(m_hash != "") {
        vector<string> v;
        ifstream fichier("database.txt");

        if (fichier) {
            string ligne;
            while(getline(fichier, ligne)) {
                v.push_back(ligne);
            }
            fichier.close();
        }

        crypt_data localData;

        #pragma omp parallel for private(localData)
        for (unsigned int i = 0; i < v.size(); i++) {
            if(!m_find) {
                localData.initialized = 0;
                if (encryptAndCompareDictionary(v[i], localData)) {
                    m_password = v[i];
                    m_find = true;
                    i = v.size();
                }
            } else {
                i = v.size();
            }
        }
    } else {
        cerr << "Error Hash not found" << endl;
    }
}


bool Functions::encryptAndCompareDictionary(string passwordCandidate, crypt_data & localData) const {
    return strcmp(crypt_r(passwordCandidate.c_str(), m_hash.c_str(), &localData), m_hash.c_str()) == 0;
}

bool Functions::encryptAndCompare(string passwordCandidate, crypt_data & localData) const{
    return strcmp(crypt_r(passwordCandidate.c_str(), m_hash.c_str(), &localData), m_hash.c_str()) == 0;
}

string Functions::getPassword() const {
    return m_password;
}

bool Functions::getFind() const {
    return m_find;
}

void Functions::initialize()
{
    m_hash = "";
    m_find = false;
    m_password = "";
}
