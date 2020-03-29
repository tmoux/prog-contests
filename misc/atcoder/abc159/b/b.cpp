#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool is(string s) {
    string t = s;
    reverse(t.begin(),t.end());
    return t == s;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int n = s.size();
    s = '#' + s;
    string a;
    for (int i = 1; i <= (n-1)/2; i++) {
        a += s[i];
    }
    string b;
    for (int i = (n+3)/2; i <= n; i++) {
        b += s[i];
    }
    cout << (is(s.substr(1))&&(is(a)&&is(b))?"Yes": "No") << '\n';
}

