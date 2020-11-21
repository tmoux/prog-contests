#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll maxn = 2e5+5, M = 998244353;
void madd(ll& a, ll b) {
    a = (a+b) % M;
}
void msub(ll& a, ll b) {
    a = (a-b+M) % M;
}
ll mult(ll a, ll b) {
    return (1LL*a*b) % M;
}
ll modexp(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
ll inverse(ll x) {
    return modexp(x,M-2);
}

int n, m;
ll d[maxn];
ll ans[maxn];

struct Shield
{
    ll a, b; 
    int id;
    bool operator<(const Shield& rhs) const {
        return b < rhs.b;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    sort(d,d+n);
    vector<Shield> shields;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        shields.push_back({a,b,i});
    }
    sort(shields.begin(),shields.end());
    int pt = 0;
    ll xsum = 0, ysum = 0;
    int y = n;
    for (int i = 0; i < n; i++) madd(ysum,d[i]%M);

    for (auto s: shields) {
        ll a = s.a;
        ll b = s.b;
        int id = s.id;
        while (pt < n && d[pt] < b) {
            madd(xsum,d[pt]%M);
            msub(ysum,d[pt]%M);
            pt++;
            y--;
        }
        ll res = 0;
        if (y+1-a >= 0) {
            ll xprob = mult(y+1-a,inverse(y+1));
            madd(res,mult(xsum,xprob));
        }
        if (y-a >= 0) {
            ll yprob = mult(y-a,inverse(y));
            madd(res,mult(ysum,yprob));
        }
        ans[id] = res;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
    }
}
