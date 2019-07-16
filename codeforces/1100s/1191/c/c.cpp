#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, k;
ll m;
deque<ll> p;

ll page(ll x, ll deleted) {
    return (x-deleted)/k;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> k;
    p.resize(m);
    for (ll i = 0; i < m; i++) {
        cin >> p[i];
        p[i]--;
    }
    ll op = 0;
    ll del = 0;
    while (!p.empty()) {
        ll pag = page(p[0],del);
        ll add = 0;
        while (!p.empty() && page(p[0],del) == pag) {
            p.pop_front();
            add++;
        }
        del += add;
        op++;
        //cout << op << endl;
    }
    cout << op << '\n';
}
