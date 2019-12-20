#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//O(n^2*m) = O(n^4)

const int maxn = 305;
int dp[maxn][maxn];
int n, m;
struct Cow
{
    int w, l, r;
} cows[maxn*maxn];

int f(int l, int r) {
    if (l > r) return 0;
    int& res = dp[l][r];
    if (res != -1) return res;
    res = 0;
    for (int i = 0; i < m; i++) {
        if (l <= cows[i].l && cows[i].l <= r) {
            res = max(res,cows[i].w+f(l,cows[i].l-1)+f(cows[i].r+1,r));
        }
        else if (l <= cows[i].r && cows[i].r <= r) {
            res = max(res,cows[i].w+f(l,cows[i].l-1)+f(cows[i].r+1,r));
        }
    }
    //printf("[%d][%d]: %d\n",l,r,res);
    return res;
}

int main() {
    freopen("pieaters.in","r",stdin); freopen("pieaters.out","w",stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> cows[i].w >> cows[i].l >> cows[i].r;    
    }
    memset(dp,-1,sizeof dp);
    int ans = f(1,n);
    cout << ans << '\n';
}

