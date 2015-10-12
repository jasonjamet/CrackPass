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

class Functions {

private:
    const char *m_hash;
    bool m_find;

    void checkForce(int longueur, char begin, char end);
    void bruteForce(int LongueurMax);

    void checkForce(char *str, int index, int max);
    bool encryptAndCompareDictionary(string passwordCandidate, crypt_data *data) const;
    bool encryptAndCompare(char * passwordCandidate) const;
    void lauchSimpleBruteForce(const char * passwordEncrypted, int maxLength);
    void lauchDictionaryBruteForce(const char * passwordEncrypted);


public:
    explicit Functions();
    ~Functions();

    void decryptPassword(const char * passwordEncrypted, int maxLength = 2);
    map<string, string> readShadowFile(string shadowFileName);
    const char * getPasswordEncryptedByName(map<string, string> userAndPass, string userName);
    

    char * getPassword() const;
    bool getFind() const;
};

#endif //CRACKPASS_FUNCTIONS_H
