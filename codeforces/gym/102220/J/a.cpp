#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int a1 = 0;
        int mx = 0;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            mx = max(mx,ai);
            if (i == 0) a1 = ai;
        }
        int ans = max(3*a1,mx+1);
        if (ans&1) ans++;
        cout << ans << '\n';
    }

}

