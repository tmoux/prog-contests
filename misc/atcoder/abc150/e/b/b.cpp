#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    string s;
    cin >> n >> s;
    int ans = 0;
    for (int i = 0; i+2 < n; i++) {
        if (s[i] == 'A' && s[i+1] == 'B' && s[i+2] == 'C') ans++;
    }
    cout << ans << '\n';
}

