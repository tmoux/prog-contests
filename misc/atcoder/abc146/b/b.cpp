#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    string s; cin >> s;
    for (char& c: s) {
        c = ((c-'A'+n)%26) + 'A';
    }
    cout << s << '\n';
}

