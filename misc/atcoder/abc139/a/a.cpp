#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s, t; cin >> s >> t;
    int ans = 0;
    for (int i = 0; i < 3; i++) {
        if (s[i] == t[i]) ans++;
    }
    cout << ans << '\n';

}

