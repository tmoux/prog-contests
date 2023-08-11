#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, k;
ll a[maxn], pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = a[i] + pre[i-1];
    }
    vector<ll> s;
    for (int i = 1; i < n; i++) {
        s.push_back(pre[i]);
    }
    sort(s.begin(),s.end());
    ll ans = 1LL*pre[n]*k;
    for (int i = 0; i < k - 1; i++) {
        ans -= s[i];
    }
    cout << ans << '\n';
}

