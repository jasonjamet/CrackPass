#ifndef CRACKPASS_FUNCTIONS_H
#define CRACKPASS_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <crypt.h>
#include <sstream>

using namespace std;


static const char characters[] = "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "&é~\"#'{([|-`è_\\^ç@à])}=+$¤£ù%*µ!§:/;.,?<>² ";

static const int characters_size = sizeof(characters) - 1;

class Functions {

private:
    const char *m_hash;
    const char *password;

    bool checkForce(char *str, int index, int max);
    bool encryptAndCompare(char *passwordEncrypted, const char * passwordCandidate);

public:
    Functions(const char *hash);

    void bruteForce(int max = 4);
};


#endif //CRACKPASS_FUNCTIONS_H

