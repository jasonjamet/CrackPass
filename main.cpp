//
// Created by etudiant on 06/10/15.
//

#include "Functions.h"

char * findEncryptedPassword(FILE* shadowFileStream) {

    cout << "Please enter a username.\n";
    string username;
    cin >> username;

    char * line = (char *) malloc(200);
    char * passwordEncrypted = NULL;
    while (fgets(line, strlen(line), shadowFileStream) != NULL) {
        cout << line << endl;
        char *token = strtok(strdup(line), ":");
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
    string shadowFileName = "./shadow";
    FILE *fp = NULL;
    fp = fopen(shadowFileName.c_str(), "r");
    cout << fp << endl;
    if (fp !=NULL) {
        char *passwordEncrypted = findEncryptedPassword(fp);
        if(passwordEncrypted != NULL) {
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