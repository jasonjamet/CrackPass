//
// Created by etudiant on 06/10/15.
//

#include "main.h"
#include "Functions.h"


char *mdp = "aaaa";



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
    // test
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
            int i;
            const char *passwordCandidate = "patrick";
            F->encryptAndCompare(passwordEncrypted, passwordCandidate);
        } else {
            cerr << "Error user not found" << endl;
        }
    } else {
        cerr << "Error during file opening" << endl;
    }
    return 0;
}