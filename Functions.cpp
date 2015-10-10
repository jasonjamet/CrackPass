
#include "Functions.h"
#include "mpi.h"
Functions::Functions(): m_hash(NULL), m_password(NULL), m_find(false) {

}

Functions::~Functions() {
    delete m_password;
}

/*
 * Read the shadow file to get an associative array of userName/encryptedPassword
 * Parameters: String (Path and name of the shadow file)
 * Return : map<string, string>
 */
map<string, string> Functions::readShadowFile(string shadowFileName) {
    map<string,string> userAndPass;

    ifstream shadowFileStream;
    shadowFileStream.open(shadowFileName);
    if (shadowFileStream.is_open()) {
        string line;
        while (getline(shadowFileStream, line)) {
            char *token = strtok(strdup(line.c_str()), ":");
            while(token != NULL) {
                userAndPass[token] = strtok (NULL, ":");
                token = strtok (NULL, ":");
            }
        }
        shadowFileStream.close();

    } else {
        cerr << "Error during file opening" << endl;
    }
    return userAndPass;
}


/*
 * Get the encrypted password of a given userName
 * Parameters: map<string, string>, userName
 * Return : const char *
 */
const char * Functions::getPasswordEncryptedByName(map<string, string> userAndPass, string userName) {
    // for (map<string ,string>::iterator it=userAndPass.begin(); it!=userAndPass.end(); ++it) {
    //     cout << it->first << " => " << it->second << '\n';
    // }
    if(!userAndPass.empty() && userAndPass.count(userName) == 1) {
        this->m_hash = userAndPass[userName].c_str();
        return this->m_hash;
    } else {
        cerr << "Error name not found, or multiple name" << endl;
        return NULL;
    }
}

/*
 * Launch a simple bruteforce to decrypt an given encrypted password.
 * Parameters: const char *, int (maxlength)
 * Return : const char *
 */
void Functions::lauchSimpleBruteForce(const char * passwordEncrypted, int maxLength) {
    if(passwordEncrypted != NULL) {
        this->bruteForce(maxLength);

        if (this->getPassword() != NULL) {
            printf("Mot de passe trouvé: %s\n", getPassword());
        } else {
            printf("Pas de mot de passe trouvée connard !\n");
        }
    } else {
        cerr << "Error password not found" << endl;
    }
}





void Functions::bruteForce(int max) {

    char *buf = (char *) malloc(max + 1);
    int i;
    
    #pragma omp master
    for (i = 1; i <= max; ++i) {

        if (m_find) {
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