#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const ll INF = 1e18;
int n, m;
ll x, k, y;
ll a[maxn], b[maxn];

ll solve(int l, int r) {
    ll endMax = 0;
    if (l != -1) endMax = max(endMax,a[l]);
    if (r != n)  endMax = max(endMax,a[r]);
    //option 1: use fireball as much as possible
    ll sz = r-l-1;
    if (sz == 0) return 0;
    ll opt1 = INF;
    if (sz >= k) opt1 = (sz/k)*x + (sz%k)*y;
    //option 2: use beserk as much as possible
    ll midMax = 0;
    for (int i = l+1; i < r; i++) {
        midMax = max(midMax,a[i]);
    }
    ll opt2 = INF;
    if (endMax > midMax) {
        opt2 = sz*y;
    }
    else if (sz >= k) {
        opt2 = x + y*(sz-k);
    }
    return min(opt1,opt2);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    cin >> x >> k >> y;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    int idx = 0;
    vector<int> v = {-1};
    bool poss = true;
    for (int i = 0; i < m; i++) {
        while (idx < n && a[idx] != b[i]) {
            idx++;
        }
        if (a[idx] != b[i]) {
            poss = false;
            break;
        }
        else {
            v.push_back(idx);
            idx++;
        }
    }
    v.push_back(n);
    if (!poss) {
        cout << -1 << '\n';
        return 0;
    }
    ll ans = 0;
    for (int i = 0; i < v.size()-1; i++) {
        ll add = solve(v[i],v[i+1]);        
        //cout << v[i] << ' ' << v[i+1] << ": " << add << endl;
        if (add == INF) {
            cout << -1 << '\n';
            return 0;
        }
        else {
            ans += add;
        }
    }
    cout << ans << '\n';
}
