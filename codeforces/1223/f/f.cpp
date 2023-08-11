#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5, M1 = 1e9+7, M2 = 1e9+9;
int q, n, a[maxn];
pair<ll,ll> hsh[maxn];

ll modexp(ll a, ll b, int M) {
    ll res = 1;
    while (b > 0) {
        if (b&1) res = (res*a) % M;
        a = (a*a) % M;
        b >>= 1;
    }
    return res;
}

ll inverse(ll x, int M) {
    return modexp(x,M-2,M);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> q;
    random_device device;
    mt19937 gen(device());
    uniform_int_distribution<int> dist(maxn,M1-1);
    int base = dist(gen);
    while (q--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        vector<int> st;
        map<pair<ll,ll>,int> mp;
        mp[make_pair(0,0)]++;
        for (int i = 1; i <= n; i++) {
            if (st.empty() || st.back() != a[i]) {
                st.push_back(a[i]);
                hsh[i].first = ((hsh[i-1].first*base)%M1 + a[i]) % M1;
                hsh[i].second = ((hsh[i-1].second*base)%M2 + a[i]) % M2;
            }
            else {
                hsh[i].first = (((hsh[i-1].first-a[i]+M1)%M1)*inverse(base,M1)) % M1;
                hsh[i].second = (((hsh[i-1].second-a[i]+M2)%M2)*inverse(base,M2)) % M2;
                st.pop_back();
            }
            mp[hsh[i]]++;
            //cout << i << ": " << hsh[i].first << ' ' << hsh[i].second << '\n';
        }
        ll ans = 0;
        for (auto p: mp) {
            ans += (1LL*p.second*(p.second-1))/2;
        }
        cout << ans << '\n';
    }
}

