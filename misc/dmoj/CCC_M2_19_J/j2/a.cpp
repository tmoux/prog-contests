#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    char prev = 'T';
    int ans = 0;
    for (int i = 0; i < 7; i++) {
        char c; cin >> c;
        if (c == 'J' && prev == 'T') ans++;
        prev = c;
    }
    cout << ans << '\n';
}

