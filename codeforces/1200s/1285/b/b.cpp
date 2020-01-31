#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        vector<ll> pre(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pre[i] = a[i];
            if (i > 0) pre[i] += pre[i-1];
        }
        multiset<ll> ms;
        ms.insert(0);
        ll ans = -1e18;
        for (int i = 0; i < n; i++) {
            if (i == n-1) {
                auto it = ms.find(0);
                ms.erase(it);
            }
            ans = max(ans,pre[i]-*ms.begin());
            ms.insert(pre[i]);
        }
        cout << (pre[n-1] > ans ? "YES" : "NO") << '\n';
    }
}

