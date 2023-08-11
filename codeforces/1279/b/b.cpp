#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
ll a[maxn], pre[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, s; cin >> n >> s;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pre[i] = pre[i-1] + a[i];
        }
        if (pre[n] <= s) {
            cout << 0 << '\n';
            continue;
        }
        int i = 1;
        pair<int,int> ans = {-1,-1};
        for (; i <= n; i++) {
            ans = max(ans,{(int)a[i],i});
            if (pre[i] > s) break;
        }
        cout << ans.second << '\n';
    }
}

