#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        set<char> good;
        int curr = 0;
        for (int i = 0; i < s.size(); i++) {
            if (i == 0 || s[i] != s[i-1]) {
                curr = 1;
            }
            else {
                curr++;
            }
            if (i == s.size()-1 || s[i] != s[i+1]) {
                if (curr&1) {
                    good.insert(s[i]);
                }
            }
        }
        
        for (char c: good) {
            cout << c;
        }
        cout << '\n';
    }
}

