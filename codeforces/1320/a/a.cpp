#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];
map<int,ll> mp;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        mp[ai-i] += ai;
    }
    ll ans = 0;
    for (auto p: mp) {
        ans = max(ans,p.second);
    }
    cout << ans << endl;
}

