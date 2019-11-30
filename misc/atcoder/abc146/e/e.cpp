#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k, a[maxn], pre[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    if (k == 1) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]--;
        pre[i] = (a[i] + pre[i-1]) % k;
    }
    map<int,int> mp;
    mp[0]++;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int add = mp[pre[i]];
        ans += add;
        mp[pre[i]]++;
        if (i-k+1 >= 0) mp[pre[i-k+1]]--;
    }
    cout << ans << '\n';
}

