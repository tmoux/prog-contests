#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M1 = 1e9+7, M2 = 1e9+9, base = 5;
inline int ctoi(char c) { return c - 'a' +1; }
pair<ll,ll> sthash(const string& s) {
    ll mult1 = 1, mult2 = 1;
    ll r1 = 0, r2 = 0;
    for (char c: s) {
        r1 = (r1 + ctoi(c) * mult1) % M1;
        r2 = (r2 + ctoi(c) * mult2) % M2;
        mult1 = (mult1 * base) % M1;
        mult2 = (mult2 * base) % M2;
    }
    return {r1,r2};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    set<pair<ll,ll>> s;
    for (int i = 0; i < n; i++) {
        string d; cin >> d;
        s.insert(sthash(d));
    }
    char v[] = {'a','b','c'};
    for (int i = 0; i < m; i++) {
        string d; cin >> d;
        bool poss = false;
        pair<ll,ll> h = sthash(d);
        pair<ll,ll> ch = h;
        ll mult1 = 1, mult2 = 1;
        for (int j = 0; j < d.size() && !poss; j++) {
            for (int k = 0; k < 3; k++) {
                if (v[k] != d[j]) {
                    ch.first = (ch.first + M1 - ctoi(d[j])*mult1 + ctoi(v[k])*mult1) % M1;
                    ch.second = (ch.second + M2 - ctoi(d[j])*mult2 + ctoi(v[k])*mult2) % M2;
                    while (ch.first < 0) ch.first += M1;
                    while (ch.second < 0) ch.second += M2;
                    if (s.count(ch)) {
                        poss = true;
                        break;
                    }
                    ch = h;
                }
            }
            mult1 = (mult1*base) % M1;
            mult2 = (mult2*base) % M2;
        }
        cout << (poss ? "YES" : "NO") << '\n';
    }

    return 0;
}

