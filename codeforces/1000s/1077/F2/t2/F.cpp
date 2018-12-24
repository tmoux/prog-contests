#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5005;
const ll NANA = -1e18;
int n, k, x, a[maxn];
ll dp[maxn][maxn];

struct Sparse
{
    //sparse table data structure for max
    static const int mk = 13;
    ll* tb[mk];
    static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
    Sparse(ll *a, int n) {
        for (int i = 0; i < mk; i++) {
            tb[i] = new ll[n+1];
            for (int j = 0; j <= n; j++) {
                tb[i][j] = 0LL;
            }
        }
        for (int i = 1; i <= n; i++) tb[0][i] = a[i];
        for (int k = 1; k <= lg(n); k++) {
            for (int i = 1; i <= n; i++) {
                int nx = i + (1<<(k-1));
                if (nx <= n) tb[k][i] = max(tb[k-1][i],tb[k-1][nx]);
                else tb[k][i] = tb[k-1][i];
            }
        }
    }
    ll getmax(int l, int r) {
        if (l > r) return 0;
        int g = lg(r-l+1);
        return max(tb[g][l],tb[g][r-(1<<g)+1]);
    }

    void del() {
        for (int i = 0; i < mk; i++) {
            delete[] tb[i];
        }
    }
};

Sparse *table;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> x;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= k; i++) {
        dp[1][i] = a[i];
    }
    table = new Sparse(dp[1],n);
    for (int j = 2; j <= x; j++) {
        for (int i = 1; i <= n; i++) {
            ll m = table->getmax(max(1,i-k),i-1);
            if (m > 0) dp[j][i] = m + a[i];
            /*
            for (int p = max(1,i-k); p < i; p++) {
                ll m = dp[j-1][p];
                if (m > 0) dp[j][i] = max(dp[j][i],m+a[i]);
            }
            */
            //cout << i << ' ' << j << ": " << dp[j][i] << '\n';
        }
        table->del();
        table = new Sparse(dp[j],n); 
    }
    ll ans = 0;
    for (int i = n-k+1; i <= n; i++) {
        ans = max(ans,dp[x][i]);
    }
    cout << (ans==0?-1:ans) << '\n';
    

    return 0;
}
