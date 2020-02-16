#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H
#include <bits/stdc++.h>
#include "cipher.h"
using namespace std;

class SubstitutionCipher : public Cipher
{
    public:
    SubstitutionCipher(string config);
    char encrypt(char c);
    char decrypt(char c);
    private:
    string sub, map;
};
#endif
