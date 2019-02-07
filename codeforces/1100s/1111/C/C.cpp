#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, k, A, B;
vector<int> a;

ll solve(int l, int r) {
    int len = r - l + 1;
    auto lo = lower_bound(a.begin(),a.end(),l);
    auto hi = upper_bound(a.begin(),a.end(),r);
    int cnt = hi - lo;
    if (cnt == 0) return A;
    if (l == r) {
        return 1LL*cnt*B;
    }
    int m = (l+r)>>1;
    return min(solve(l,m) + solve(m+1,r), 1LL*B*cnt*len);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> A >> B;
    a.resize(k);
    for (int i = 0; i < k; i++) cin >> a[i];
    sort(a.begin(),a.end());
    ll ans = solve(1,1<<n);
    cout << ans << '\n';

    return 0;
}

