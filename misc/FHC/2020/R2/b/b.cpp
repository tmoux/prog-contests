#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 8005;
int N;
ld P, Q;

ld dp[maxn][maxn];

ld f(int lo, int hi) {
    ld& res = dp[lo][hi];
    if (res >= 0) {
        return res;
    }
    if (lo == 0 && hi == 0) {
        return res = 0;
    }
    res = 0;
    //hi and hi match up
    if (hi > 0) {
        res += (hi*(hi-1)/2)*(1+f(lo,hi-1));
    }
    //lo and lo match up
    if (lo > 0) {
        res += (lo*(lo-1)/2)*(1+f(lo-1,hi));
    }
    //lo and hi match up
    int x = lo+1+hi;    
    int tot = x*(x-1)/2;
    if (lo > 0 && hi > 0) {
        res += ((ld)(lo*hi))*P*(1+f(lo-1,hi));
        res += ((ld)(lo*hi))*Q*(1+f(lo,hi-1));
    }
    //lo and me match up
    if (lo > 0) {
        res += ((ld)(lo))*P*(1+f(lo-1,hi));
        res += ((ld)(lo))*Q*(1);
    }
    //hi and me match up
    if (hi > 0) {
        res += ((ld)(hi))*P*(1);
        res += ((ld)(hi))*Q*(1+f(lo,hi-1));
    }
    res /= (ld)tot;
    return res;
}

void solve() {
    cin >> N >> P;
    Q = 1-P;
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = -1;
        }
    }
    for (int i = 1; i <= N; i++) {
        cout << f(i-1,N-i) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(10);
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ":\n";
        solve();
    }
}
