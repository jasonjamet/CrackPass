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


    void checkForce(char *str, int index, int max);
    bool encryptAndCompareDictionary(string passwordCandidate) const;
    bool encryptAndCompare(char * passwordCandidate) const;



public:
    explicit Functions();
    ~Functions();

    map<string, string> readShadowFile(string shadowFileName);
    const char * getPasswordEncryptedByName(map<string, string> userAndPass, string userName);
    void launchDictionaryBruteForce();
    void launchSimpleBruteForce(int maxLength = 2);
    

    char * getPassword() const;
    bool getFind() const;
};

#endif //CRACKPASS_FUNCTIONS_H
