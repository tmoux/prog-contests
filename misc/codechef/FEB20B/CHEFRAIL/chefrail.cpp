#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, M;
int off = 100001;
bool x[maxn<<1], y[maxn<<1];

ll ans = 0;
map<int,int> mp;
vector<pair<int,int>> v;
void factor(int x) {
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                mp[i] += 2;
                x /= i;
            }
            factor(x);
            return;
        }
    }
    if (x > 1) mp[x] += 2;
}

void checkX(ll fac, ll sq, int i, bool check) {
    ll j = sq/fac;
    if (fac <= j) {
        if (check && fac <= 100000 && j <= 100000) {
            if (y[off+j] && y[off-fac]) ans++;
            if (j != fac && y[off-j] && y[off+fac]) ans++;
        }

        if (i < v.size()) {
            for (int k = 0; k <= v[i].second; k++) {
                checkX(fac,sq,i+1,k!=0);
                fac *= v[i].first;
            }
        }
    }
}

void checkY(ll fac, ll sq, int i, bool check) {
    ll j = sq/fac;
    if (fac <= j) {
        if (check && fac <= 100000 && j <= 100000) {
            if (x[off+j] && x[off-fac]) ans++;
            if (j != fac && x[off-j] && x[off+fac]) ans++;
        }

        if (i < v.size()) {
            for (int k = 0; k <= v[i].second; k++) {
                checkY(fac,sq,i+1,k!=0);
                fac *= v[i].first;
            }
        }
    }
}

void solve() {
    memset(x,false,sizeof x);
    memset(y,false,sizeof y);
    cin >> N >> M;
    vector<int> xs, ys;
    bool hasO = false;
    for (int i = 0; i < N; i++) {
        int xi; cin >> xi;
        if (xi == 0) {
            hasO = true;
            continue;
        }
        x[xi+off] = true;
        xs.push_back(xi);
    }
    for (int i = 0; i < M; i++) {
        int yi; cin >> yi;
        if (yi == 0) {
            hasO = true;
            continue;
        }
        y[yi+off] = true;
        ys.push_back(yi);
    }
    ans = 0;
    for (int xi: xs) {
        ll sq = 1LL*xi*xi;
        mp.clear();
        v.clear();
        factor(abs(xi));
        for (auto p: mp) v.push_back(p);
        checkX(1,sq,0,true);
    }

    for (int yi: ys) {
        ll sq = 1LL*yi*yi;
        mp.clear();
        v.clear();
        factor(abs(yi));
        for (auto p: mp) v.push_back(p);
        checkY(1,sq,0,true);
    }

    if (hasO) {
        ans += 1LL*((int)xs.size())*((int)ys.size());
    }
    cout << ans << '\n';
}

int main()
{
    int t; cin >> t;
    while (t--) solve();
}
