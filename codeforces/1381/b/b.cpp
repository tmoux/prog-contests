#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4005;
int n;
int p[maxn];
bool ismx[maxn];

int dp[maxn][maxn][2]; //[pos][# in first array][which one]

int f(int i, int j, int w) {
    int& res = dp[i][j][w];
    if (res != -1) return res;
    if (i == 2*n) {
        return res = (j == n);
    }
    res = 0;
    if (w == 0) { //on first
        res = f(i+1,j+1,w);
        if (ismx[i]) res |= f(i+1,j,w^1);
    }
    else {
        res = f(i+1,j,w);
        if (ismx[i]) res |= f(i+1,j+1,w^1);
    }
    //cout << i << ' ' << j << ' ' << w << ": " << res << endl;
    return res;
}

void solve() {
    cin >> n;
    for (int i = 0; i <= 2*n; i++) {
        for (int j = 0; j <= 2*n; j++) {
            dp[i][j][0] = dp[i][j][1] = -1;
        }
    }
    int mx = 0;
    for (int i = 0; i < 2*n; i++) {
        cin >> p[i];
        ismx[i] = p[i] > mx;
        mx = max(mx,p[i]);
    }
    int ans = f(0,0,0);
    cout << (ans?"YES":"NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
