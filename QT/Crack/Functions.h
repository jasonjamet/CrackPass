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
    char * m_password;
    bool m_find;

    void checkForce(int longueur, char begin, char end);
    void bruteForce(int LongueurMax = 2);

    void checkForce(char *str, int index, int max);
    bool encryptAndCompareDictionary(string passwordCandidate, crypt_data *data) const;
    bool encryptAndCompare(char * passwordCandidate) const;
    void lauchSimpleBruteForce(const char * passwordEncrypted, int maxLength);



public:
    explicit Functions();
    ~Functions();

    map<string, string> readShadowFile(string shadowFileName);
    const char * getPasswordEncryptedByName(map<string, string> userAndPass, string userName);
    void lauchDictionaryBruteForce(const char * passwordEncrypted);
    

    char * getPassword() const;
    bool getFind() const;
};

#endif //CRACKPASS_FUNCTIONS_H
