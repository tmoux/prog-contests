#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e4+4, maxk = 105;
const ll INF = 1e18;
int N, K;
ll dp[maxk][maxn];
ll A[maxn];
inline ll sqr(ll a) { return a*a; };

void dnc(int l, int r, int optl, int optr, int k) {
    if (l > r) return;
    int m = (l+r)>>1;
    pair<ll,int> best = {INF,-1};
    for (int j = 1; j <= min(r,m-1); j++) {
        best = min(best,{dp[k-1][j]+sqr(A[m]-A[j+1]),j});
    }
    int opt = best.second;
    dp[k][m] = best.first;
    dnc(l,m-1,optl,opt,k);
    dnc(m+1,r,opt,optr,k);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }    
    for (int i = 1; i <= N; i++) {
        for (int k = 1; k <= K; k++) {
            dp[k][i] = INF;
        }
    }
    for (int i = 1; i <= N; i++) {
        dp[1][i] = sqr(A[i]-A[1]);
    }
    for (int k = 2; k <= K; k++) {
        dnc(1,N,1,N,k);
    }
    cout << dp[K][N] << '\n';

    return 0;
}

