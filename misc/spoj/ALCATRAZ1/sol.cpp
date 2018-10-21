#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    string s; cin >> s;
    int r = 0;
    for (char c: s) r += (c-'0'); cout << r << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t; while (t--) solve();
    return 0;
}

