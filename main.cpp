//
// Created by etudiant on 06/10/15.
//

#include "Functions.h"

char * findEncryptedPassword(ifstream* shadowFileStream) {

    cout << "Please enter a username.\n";
    string username;
    cin >> username;

    string line;
    char * passwordEncrypted = NULL;
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
    string shadowFileName = "/home/etudiant/Damota/CrackPass/shadow";
    ifstream shadowFileStream;
    shadowFileStream.open(shadowFileName);
    if (shadowFileStream.is_open()) {
        char * passwordEncrypted = findEncryptedPassword(&shadowFileStream);
        if(passwordEncrypted != NULL) {
            shadowFileStream.close();
            Functions *F = new Functions(passwordEncrypted);
            F->bruteForce(4);
            delete (F);
        } else {
            cerr << "Error user not found" << endl;
        }
    } else {
        cerr << "Error during file opening" << endl;
    }
    return 0;
}