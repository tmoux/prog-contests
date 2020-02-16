#include <bits/stdc++.h>
#include "substitution.h"
using namespace std;

SubstitutionCipher::SubstitutionCipher(string config) {
    sub = config;
    map = config;
    for (int i = 0; i < 26; i++) {
        map[config[i]-'A'] = i+'A';
    }
    //cout << sub << ' ' << map << '\n';
}
char SubstitutionCipher::encrypt(char c) {
    return sub[c-'A'];
}
char SubstitutionCipher::decrypt(char c) {
    return map[c-'A'];
}
