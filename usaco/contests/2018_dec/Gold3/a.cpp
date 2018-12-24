#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e4+4, maxk = 1e3+3;
int N, K;
struct Sparse
{
    //sparse table data structure for max
    const int mk = 15;
    int* tb[15];
    static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
    Sparse(int *a, int n) {
        for (int i = 0; i < mk; i++) {
            tb[i] = new int[n];
        }
        for (int i = 0; i < n; i++) tb[0][i] = a[i];
        for (int k = 1; k <= lg(n); k++) {
            for (int i = 0; i < n; i++) {
                int nx = i + (1<<(k-1));    
                if (nx < n) tb[k][i] = max(tb[k-1][i],tb[k-1][nx]);
                else tb[k][i] = tb[k-1][i];
            }
        }
    }
    int getmax(int l, int r) {
        int g = lg(r-l+1);
        return max(tb[g][l],tb[g][r-(1<<g)+1]);
    }
};

int a[maxn];
int dp[maxn][maxk];
int f(int i, int j, Sparse& st) {
    if (dp[i][j] >= 0) return dp[i][j];
    if (i == N) {
        return dp[i][j] = j*st.getmax(i-j,i-1);
    }
    if (j == K) {
        return dp[i][j] = j*st.getmax(i-j,i-1) + f(i+1,1,st);
    }
    dp[i][j] = max(j*st.getmax(i-j,i-1) + f(i+1,1,st),
                          f(i+1,j+1,st));
    //cout << i << ' ' << j << ": " << dp[i][j] << '\n';
    return dp[i][j];
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("teamwork.in","r",stdin); freopen("teamwork.out","w",stdout);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    Sparse st(a,N);
    memset(dp,-1,sizeof dp);
    int ans = f(1,1,st);
    cout << ans << '\n';

    return 0;
}

