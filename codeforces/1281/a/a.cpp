#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; 
        cin >> s;
        int n = s.size();
        if (s.substr(n-2) == "po") {
            cout << "FILIPINO\n";
        }
        else if (s.substr(max(0,n-4)) == "desu" || s.substr(max(0,n-4)) == "masu") {
            cout << "JAPANESE\n";
        }
        else {
            cout << "KOREAN\n";
        }
    }
}

