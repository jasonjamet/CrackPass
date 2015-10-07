//
// Created by etudiant on 06/10/15.
//

#ifndef CRACKPASS_FUNCTIONS_H
#define CRACKPASS_FUNCTIONS_H

#include <iostream>
#include <string>

using namespace std;


static const char characters[] = "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "&é~\"#'{([|-`è_\\^ç@à])}=+$¤£ù%*µ!§:/;.,?<>² ";

static const int characters_size = sizeof(characters) - 1;

class Functions {

private:
    string m_salt;
    const char *m_hash;
    const char *password;

    bool checkForce(char *str, int index, int max);

public:
    Functions(string salt, const char *hash);

    bool encryptAndCompare(char *passwordEncrypted, const char * passwordCandidate);
    void bruteForce(int max = 4);
};


#endif //CRACKPASS_FUNCTIONS_H

