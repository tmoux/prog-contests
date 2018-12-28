#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 4005, maxk = 805;
const ll INF = 1e18;
int N, K;
ll u[maxn][maxn];
ll dp[maxk][maxn];

ll getsum(int l, int r) {
    return (u[r][r] - u[l-1][r] - u[r][l-1] + u[l-1][l-1])/2;
}

void dnc(int l, int r, int optl, int optr, int k) {
    if (l > r) return;
    int m = (l+r)>>1;
    int opt;
    pair<ll,int> best = {INF,-1};
    for (int j = optl; j <= min(m-1,optr); j++) {
        best = min(best,{dp[k-1][j]+getsum(j+1,m),j});
    }
    //cout << best.first << ' ' << best.second << ' ' << m << '\n';
    opt = best.second;
    dp[k][m] = best.first;
    /*
    if (opt == -1) {
        dnc(l,m-1,optl,optr,k);
        dnc(m+1,r,optl,optr,k);
    }
    */
    //else {
        dnc(l,m-1,optl,opt,k);
        dnc(m+1,r,opt,optr,k);
    //}
}

int main()
{
    scanf("%d %d\n",&N,&K);
    char buffer[10000];
    for (int i = 1; i <= N; i++) {
        gets(buffer);
        for (int j = 1; j <= N; j++) {
            u[i][j] = buffer[2*(j-1)]-'0';
            u[i][j] = u[i][j] + u[i-1][j] + u[i][j-1] - u[i-1][j-1];
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int k = 2; k <= K; k++) {
            dp[k][i] = INF;
        }
        dp[1][i] = getsum(1,i);
    }
    for (int k = 2; k <= K; k++) {
        dnc(1,N,1,N,k);
        /*
        for (int i = 1; i <= N; i++) {
            cout << dp[k][i] << ' ';            
        }
        cout << '\n';
        */
    }
    cout << dp[K][N] << '\n';

    return 0;
}

