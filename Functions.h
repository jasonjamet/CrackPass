#ifndef CRACKPASS_FUNCTIONS_H
#define CRACKPASS_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#include <sstream>
#include <map>
#include <mpi.h>
#include <omp.h>
#include <vector>
#include <cmath>

using namespace std;

static const char characters[] = "abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"0123456789";
//"&é~\"#'{([|-`è_\\^ç@à])}=+$¤£ù%*µ!§:/;.,?<>² ";

static const int characters_size = sizeof(characters) - 1;

struct crypt_data;

class Functions {

public:
    string m_hash;
    string m_password;


    bool m_find;

    void checkForce(string str, int index, int max, const crypt_data & localData);
    bool encryptAndCompareDictionary(string passwordCandidate, crypt_data & data) const;
    bool encryptAndCompare(string passwordCandidate, crypt_data & data) const;

    void bruteSequentialMPI(char x, int maxLen);
    void bruteImplMPI(char * str, int index, int maxDepth, crypt_data & localData);

    void bruteSequential(char x, int maxLen);
    void bruteImpl(char * str, int index, int maxDepth, crypt_data & localData);

public:
    explicit Functions();
    ~Functions();

    map<string, string> readShadowFile(string shadowFileName) const;
    void setPasswordEncryptedByName(map<string, string> userAndPass, string userName);


    void launchDictionaryBruteForceMPI();
    void launchSimpleBruteForceMPI(int max = 5);

    void launchDictionaryBruteForce();
    void launchSimpleBruteForce(int max = 5);

    bool getFind() const;
    string getHash() const;
    void setHash(const char * hash);
    string getPassword() const;
};

#endif //CRACKPASS_FUNCTIONS_H
