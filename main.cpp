//
// Created by etudiant on 06/10/15.
//

#include "QT/Crack/Functions.h"

static const char alphabet[] =
        "abcdefghijklmnopqrstuvwxyz"
               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
static const int alphabetSize = sizeof(alphabet) - 1;

char * m_hash =  "$1$KzWGv3OY$SYOrFT3pq570C8snr6.XN/";

bool encryptAndCompare(char * passwordCandidate, crypt_data data ) {
    return strcmp(crypt_r(passwordCandidate, m_hash, &data), m_hash) == 0;
}

void bruteImpl(char* str, int index, int maxDepth, crypt_data localData) {
    for (int i = 0; i < alphabetSize; ++i) {
        str[index] = alphabet[i];
        if (index == maxDepth - 1) {
            if(str[0] == 'j' && str[1] == 'd') {
                //cout << str << endl;
            }
            if(encryptAndCompare(str, localData)) {
                cout << "trouve " <<  str << endl;
            }

        }
        else {
            bruteImpl(str, index + 1, maxDepth, localData);
        }
    }
}

void bruteSequential(char x, int maxLen) {
    char* buf = (char *) malloc(maxLen + 1);
    buf[0] = x;
    crypt_data localData;

    #pragma omp parallel for private(localData)
    for (int i = 2; i <= maxLen; ++i) {
        buf[i]='\0';
        bruteImpl(buf, 1, i, localData);
    }

    free(buf);
}

void launchParallelBF(int maxLen) {
    #pragma omp parallel for
    for (int k = 0; k < alphabetSize; k++) {
        bruteSequential(alphabet[k], maxLen);
    }
}



int main(int argc, char *argv[]) {


    Functions *F = new Functions();
    //F->lauchSimpleBruteForce(F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason"), 4);
    F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason");
    F->launchDictionaryBruteForce();
    //F->launchSimpleBruteForce(3);
    delete (F);

    //launchParallelBF(3);


    return 0;
}

