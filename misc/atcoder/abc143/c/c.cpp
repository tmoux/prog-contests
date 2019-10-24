#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (i == n-1 || s[i] != s[i+1]) ans++;    
    }
    cout << ans << '\n';
}

