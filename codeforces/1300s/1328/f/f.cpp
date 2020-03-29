#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k, a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    map<ll,int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ++mp[a[i]];
    }
    pair<ll,int> lo = {0,0};
    pair<ll,int> hi = {0,0};
    for (int i = 0; i < n; i++) {
        ++hi.second;
        hi.first += a[i];
    }
    ll ans = 1LL<<62;
    for (auto p: mp) {
        ll x = p.first;
        int need = k-p.second;
        if (need <= 0) {
            cout << 0 << '\n';
            return 0;
        }
        hi.second -= p.second;
        hi.first -= 1LL*p.second*x;

        ll loCost = 1LL*lo.second*(x-1)-lo.first;
        ll hiCost = hi.first-1LL*hi.second*(x+1);

        if (lo.second >= need) {
            ans = min(ans,loCost+need);
        }
        if (hi.second >= need) {
            ans = min(ans,hiCost+need);
        }
        if (lo.second+hi.second >= need) {
            ans = min(ans,loCost+hiCost+need);
        }

        lo.second += p.second;
        lo.first += 1LL*p.second*x;
    }
    cout << ans << '\n';
}
