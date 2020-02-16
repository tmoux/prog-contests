#include <bits/stdc++.h>
#include "cipher.h"
#include "substitution.h"
using namespace std;

int main() {
    Cipher *my_cipher;
    string config = "EFGHIJKLMNOPQRSTUVWXYZABCD";
    my_cipher = new SubstitutionCipher(config);
    cout << 'A' << ": " << my_cipher->encrypt('A') << endl;
    cout << 'A' << ": " << my_cipher->decrypt('A') << endl;
}
