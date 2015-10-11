#ifndef CRACKPASS_FUNCTIONS_H
#define CRACKPASS_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include <sstream>
#include <map>

using namespace std;


static const char characters[] =  "0123456789";// "abcdefghijklmnopqrstuvwxyz"
       // "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

//"&é~\"#'{([|-`è_\\^ç@à])}=+$¤£ù%*µ!§:/;.,?<>² "

static const int characters_size = sizeof(characters) - 1;

class Functions {

private:
    const char *m_hash;
    char * m_password;
    bool m_find;

    void checkForce(char *str, int index, int max);
    bool encryptAndCompareDictionary(string passwordCandidate, crypt_data *data) const;
    bool encryptAndCompare(char * passwordCandidate) const;


public:
    Functions();
    ~Functions();

    map<string, string> readShadowFile(string shadowFileName);
    const char * getPasswordEncryptedByName(map<string, string> userAndPass, string userName);
    void lauchSimpleBruteForce(const char * passwordEncrypted, int maxLength);
    void lauchDictionaryBruteForce(const char * passwordEncrypted);

    void bruteForce(int max = 4);

    char * getPassword() const;
};


// [aA-zZ0-9&é~"#'{([|\-`è_\^ç@à\=+$¤£\])ù%*µ!§:};.,?<>² \/\\]+

#endif //CRACKPASS_FUNCTIONS_H
