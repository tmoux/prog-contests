#ifndef CIPHER_H
#define CIPHER_H
#include <bits/stdc++.h>
using namespace std;

class Cipher
{
    public:
    Cipher();
    Cipher(string config);
    virtual char encrypt(char c) = 0;
    virtual char decrypt(char c) = 0;
};
#endif
