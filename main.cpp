//
// Created by etudiant on 06/10/15.
//

#include "Functions.h"

/* Comments and TODDO
 *
 *
 *
 *
 */
#include "main.h"


char *mdp = "aaaa";


/*
 * Encrypt the candidate password, and compare it to the real encrypted password
 * Arguments passwordEncrypted, passwordCandidate
 * Return bool
 */
bool encryptAndCompare(char *passwordEncrypted, const char * passwordCandidate) {

    char * passwordCandidateEncrypted = crypt(passwordCandidate, passwordEncrypted);

    if(strcmp(passwordEncrypted, passwordCandidateEncrypted) == 0) {
        cout << "Match" << endl;
        return true;
    } else {
        return false;
    }
}

char * findEncryptedPassword(ifstream* shadowFileStream) {

    cout << "Please enter a username.\n";
    string username;
    cin >> username;

    string line;
    char * passwordEncrypted;
    while (getline(*shadowFileStream, line)) {
        char *token = strtok(strdup(line.c_str()), ":");
        while(token != NULL) {
            if(strcmp(username.c_str(),token) == 0) {
                token = strtok (NULL, ":");
                passwordEncrypted = token;
                break;
            }
            token = strtok (NULL, ":");
        }
    }
    return passwordEncrypted;

}


int main() {

    Functions *F = new Functions("salt", mdp);

    F->bruteForce(4);

    delete (F);

    string shadowFileName = "/home/jason/Dropbox/git/CrackPass/shadow";
    ifstream shadowFileStream;
    shadowFileStream.open(shadowFileName);
    if (shadowFileStream.is_open()) {
        char * passwordEncrypted = findEncryptedPassword(&shadowFileStream);
        if(passwordEncrypted != NULL) {
            shadowFileStream.close();
            const char *passwordCandidate = "patrick";
            encryptAndCompare(passwordEncrypted, passwordCandidate);
        } else {
            cerr << "Error user not found" << endl;
        }
    } else {
        cerr << "Error during file opening" << endl;
    }
    return 0;
}