#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 305;
int dp[1<<22];
int n, m;
struct Cow
{
    int w, l, r;
} cows[maxn*maxn];

int f(int mask) {
    if (dp[mask] != -1) return dp[mask];
    dp[mask] = 0;
    vector<int> v(n+1,1);
    for (int i = 0; i < m; i++) {
        if (mask & (1<<i)) {
            for (int j = cows[i].l; j <= cows[i].r; j++) {
                v[j] = 0;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        if (!(mask & (1<<i))) {
            bool poss = false;
            for (int j = cows[i].l; j <= cows[i].r; j++) {
                if (v[j] == 1) {
                    poss = true;
                }
            }
            if (poss) {
                dp[mask] = max(dp[mask],cows[i].w+f(mask|(1<<i)));
            }
        }
    }
    return dp[mask];
}

int main() {
    freopen("pieaters.in","r",stdin); freopen("pieaters.out","w",stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> cows[i].w >> cows[i].l >> cows[i].r;    
    }
    memset(dp,-1,sizeof dp);
    int ans = f(0);
    cout << ans << '\n';
}

