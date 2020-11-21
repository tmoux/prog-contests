#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string S, P; cin >> S >> P;
    bool is = false;
    if (S == P) {
        is = true;
    }
    for (char d = '0'; d <= '9'; d++) {
        if (S == P+d || S == d+P) {
            is = true;
        }
    }
    for (auto& c: P) {
        if (isupper(c)) c = tolower(c);
        else if (islower(c)) c = toupper(c);
    }
    if (S == P) is = true;
    cout << (is?"Yes":"No") << '\n';
}
