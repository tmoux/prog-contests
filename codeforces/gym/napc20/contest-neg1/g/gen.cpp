#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    random_device device;
    mt19937 gen(device());
    string s(n,'0'), t(n,'0');
    for (int i = 0; i < n; i++) {
        int r = gen() % 2;
        char c = r?'0':'1';
        s[i] = t[i] = c;
    }
    //cout << s << ' ' << t << '\n';
    for (int j = 0; j < 10000; j++) {
        int i = gen() % n;
        if (s[i] == s[(i+1)%n]) {
            s[i] = s[i]=='0'?'1':'0';
            s[(i+1)%n] = s[(i+1)%n]=='0'?'1':'0';
        }
    }
    for (int j = 0; j < 10000; j++) {
        int i = gen() % n;
        if (t[i] == t[(i+1)%n]) {
            t[i] = t[i]=='0'?'1':'0';
            t[(i+1)%n] = t[(i+1)%n]=='0'?'1':'0';
        }
    }
    cout << s << '\n' << t << '\n';
}

