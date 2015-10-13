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

static const char characters[] = "abcdefghijklmnopqrstuvwxyz";
        //"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        //"0123456789";
//"&é~\"#'{([|-`è_\\^ç@à])}=+$¤£ù%*µ!§:/;.,?<>² ";

static const int characters_size = sizeof(characters) - 1;

struct crypt_data;

class Functions {

private:
    const char *m_hash;
    char * m_password;
    bool m_find;

    bool encryptAndCompareDictionary(string passwordCandidate, crypt_data data) const;
    bool encryptAndCompare(char * passwordCandidate, crypt_data data) const;

    void bruteSequential(char x, int maxLen);
    void bruteImpl(char* str, int index, int maxDepth, crypt_data localData);

public:
    explicit Functions();
    ~Functions();

    map<string, string> readShadowFile(string shadowFileName);
    const char * getPasswordEncryptedByName(map<string, string> userAndPass, string userName);

    void launchDictionaryBruteForce();
    void launchSimpleBruteForce(int max = 2);
    

    char * getPassword() const;
    bool getFind() const;


};

#endif //CRACKPASS_FUNCTIONS_H
