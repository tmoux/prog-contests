#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int N; cin >> N;
        int ans = 999999999;
        while (N--) {
            int p, v; cin >> p >> v;
            ans = min(ans,p-v);
        }
        cout << ans << '\n';
    }
}

