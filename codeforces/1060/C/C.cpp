#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll maxn = 2005, INF = 2e9+9;
ll n, m, A[maxn], B[maxn], x;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> A[i];
        A[i] += A[i-1];
    }
    for (ll i = 1; i <= m; i++) {
        cin >> B[i];
        B[i] += B[i-1];
    }
    cin >> x;
    ll mp[maxn]; //len to min sum
    for (ll i = 0; i <= m; i++) {
        mp[i] = INF;
    }
    for (ll i = 1; i <= m; i++) {
        for (ll j = i; j <= m; j++) {
            mp[j-i+1] = min(mp[j-i+1],B[j]-B[i-1]);
        }
    }
    vector<pair<ll,ll>> vp;
    for (ll i = 1; i <= m; i++) {
        vp.push_back({mp[i],i});
    }
    sort(vp.begin(),vp.end());
    ll maxans = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = i; j <= n; j++) {
            ll s = A[j] - A[i-1];
            pair<ll,ll> r = {x / s,INF};
            auto it = upper_bound(vp.begin(),vp.end(),r);
            if (it == vp.begin()) continue;
            --it;
            maxans = max(maxans,(j-i+1)*it->second);
            //cout << (j-i+1) << ' ' << it->second << '\n';
        }
    }
    cout << maxans << '\n';


    return 0;
}

