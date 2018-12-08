#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+9;
const int maxn = 1005;
const int maxk = 12;
int N, M, K, dp[maxn][maxn][maxk], pfx[maxn][maxn][maxk], fj[maxn], fp[maxn];

inline void add(int& a, int b) { a = (a+b) % MOD; }

int main()
{
	freopen("team.in","r",stdin); freopen("team.out","w",stdout);
    scanf("%d %d %d",&N,&M,&K);
    for (int i = 1; i <= N; i++) scanf("%d",fj+i);
    for (int i = 1; i <= M; i++) scanf("%d",fp+i);
    sort(fj+1,fj+N+1);
    sort(fp+1,fp+M+1);
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            dp[i][j][0] = 1;
            pfx[i][j][0] = 1;
        }
    }
    for (int k = 0; k <= K; k++) {
        for (int i = 1; i <= N; i++) {
            int a = 1;
            for (int j = 1; j <= M; j++) {
                if (k == 0) dp[i][j][k] = 1;
                else {
                    dp[i][j][k] = dp[i-1][j][k];
                    while (fj[i] > fp[a] && a <= j) a++;
                    if (a > 1) add(dp[i][j][k],pfx[i-1][a-2][k-1]);    
                }
                pfx[i][j][k] = dp[i][j][k];
                add(pfx[i][j][k],pfx[i][j-1][k]);
            }
        }
    }

    printf("%d\n",dp[N][M][K]);
	return 0;
}

