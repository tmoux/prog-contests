#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n, m[maxn][maxn];

ll sqflr(ll x) {
    ll r = (ll)(sqrt(x)) + 5;
    while (r*r > x) r--;
    assert(r*r == x);
    return r;
}

ll ans[maxn];

void print() {
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    exit(0);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
        }
    }
    ll gc = 0;
    for (ll j = 1; j < n; j++) {
        gc = __gcd(gc,(ll)m[0][j]);
    }
    ans[0] = gc;
    
    for (int i = 1; i < n; i++) {
        ans[i] = m[0][i]/gc;
    }

    /*
    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            //cout << ans[i] << ' ' << ans[j] << ": " << (ans[i]*ans[j]) << '\n';
            if (ans[i] * ans[j] != m[i][j]) {
                ll fac = m[i][j] / (ans[i] * ans[j]);
                ll r = sqflr(fac);
                for (int k = 1; k < n; k++) {
                    ans[k] *= r;
                }
                ans[0] /= r;
                print();
            }
        }
    }
    print();
}

