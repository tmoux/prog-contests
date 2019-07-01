#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, s, t; cin >> n >> s >> t;
        int c = (s+t)-n;
        s -= c;
        t -= c;
        int ans = max(s+1,t+1);
        cout << ans << '\n';
    }
}

