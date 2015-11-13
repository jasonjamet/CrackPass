#include "Functions.h"

Functions::Functions(): m_hash(""), m_find(false) {

}

Functions::~Functions() {
}
/*******************************************************************************
************************Read file / get name / get password*********************
********************************************************************************/


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








/*******************************************************************************
************************BF and BF dico with openmp and MPI**********************
********************************************************************************/

void Functions::bruteImplMPI(char* str, int index, int maxDepth, crypt_data & localData) {

    for (int i = 0; i < characters_size; ++i) {
        if(!m_find) {
            localData.initialized = 0;

            str[index] = characters[i];
            if (index == maxDepth - 1) {
                if (encryptAndCompare(str, localData)) {
                    m_find = true;
                    i = characters_size;
                    MPI_Send(str, 100, MPI_CHAR, 0, 7, MPI_COMM_WORLD);
                }
            }
            else {
                bruteImplMPI(str, index + 1, maxDepth, localData);
            }
        } else {
            i =  characters_size;
        }

    }
}

void Functions::bruteSequentialMPI(char x, int maxLen)  {
    crypt_data localData;
    char* buf = (char *) malloc(maxLen + 1);

    buf[0] = x;
    #pragma omp parallel for private(localData)
    for (int i = 2; i <= maxLen; ++i) {
        if (!m_find) {
            buf[i]='\0';
            bruteImplMPI(buf, 1, i, localData);
        } else {
            i = maxLen+1;
        }
    }

    free(buf);
}

void Functions::launchSimpleBruteForceMPI(int max) {

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int groupSize = floor(characters_size / size-2);

    #pragma omp parallel for
    for (int i = (rank -1) * groupSize; i < rank * groupSize; i++) {
            if (!m_find) {
                bruteSequentialMPI(characters[i], max);
            } else {
                i = characters_size;
            }
    }

    if (rank == size - 1) {
        #pragma omp parallel for
        for (int i = (rank -1) * groupSize; i < characters_size; i++) {
            if (!m_find) {
                bruteSequentialMPI(characters[i], max);
            } else {
                i = characters_size;
            }
        }
    }
}

void Functions::launchDictionaryBruteForceMPI() {
  if(m_hash != "") {
      vector<string> v;
      int size, rank;
      MPI_Comm_size(MPI_COMM_WORLD, &size);
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);
      ifstream fichier("database.txt");

      if (fichier) {
          string ligne;
          while(getline(fichier, ligne)) {
              v.push_back(ligne);
          }
          fichier.close();
      }

      crypt_data localData;

      int groupSize = floor(v.size()/ size-2);
      #pragma omp parallel for private(localData)
      for (int i = (rank -1) * groupSize; i < rank * groupSize; i++) {
          if (!m_find) {
              localData.initialized = 0;
              if (encryptAndCompareDictionary(v[i], localData)) {
                  string tmp = v[i];
                  m_find = true;
                  i = v.size();
                  MPI_Send((char*)tmp.c_str(), 100, MPI_CHAR, 0, 7, MPI_COMM_WORLD);
              }
          } else {
              i = v.size();
          }
      }

      if (rank == size - 1) {
          #pragma omp parallel for
          for (unsigned int i = (rank -1) * groupSize; i < v.size(); i++) {
              if (!m_find) {
                  localData.initialized = 0;
                  if (encryptAndCompareDictionary(v[i], localData)) {
                      string tmp = v[i];
                      m_find = true;
                      i = v.size();
                      MPI_Send((char*)tmp.c_str(), 100, MPI_CHAR, 0, 7, MPI_COMM_WORLD);
                  }
              } else {
                  i = v.size();
              }
          }
      }
  } else {
      cerr << "Error Hash not found" << endl;
  }
}


/*******************************************************************************
************************BF and BF dico with only openMp****************************
********************************************************************************/

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
        ifstream fichier;
        fichier.open("database.txt");

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
                    string tmp = v[i];
                    m_find = true;
                    cout << tmp << endl;
                    m_password = tmp;
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

bool Functions::getFind() const {
    return m_find;
}

string Functions::getHash() const {
    return m_hash;
}

void Functions::setHash(const char * hash) {
    m_hash = hash;
}


string Functions::getPassword() const {
    return m_password;
}
