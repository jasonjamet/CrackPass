#ifndef CRACKPASS_FUNCTIONS_H
#define CRACKPASS_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
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
    char *m_password;

    void checkForce(char *str, int index, int max);
    bool encryptAndCompare(const char * passwordCandidate);

public:
    Functions(const char *hash);
    ~Functions();

    void bruteForce(int max = 4);
};


// [aA-zZ0-9&é~"#'{([|\-`è_\^ç@à\=+$¤£\])ù%*µ!§:};.,?<>² \/\\]+

#endif //CRACKPASS_FUNCTIONS_H
