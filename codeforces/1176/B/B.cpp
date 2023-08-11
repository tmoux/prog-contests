#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int c1 = 0, c2 = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            if (ai % 3 == 1) c1++;
            else if (ai % 3 == 2) c2++;
            else ans++;
                
        }
        int add = min(c1,c2);
        ans += add; c1 -= add;
        c2 -= add;
        ans += (c1/3);
        ans += (c2/3);
        cout << ans << '\n';
    }
}

