#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    string t = s.substr(0,n/2);
    if (s == t+t) {
        cout << "Yes\n";
    }
    else {
        cout << "No\n";
    }
}

