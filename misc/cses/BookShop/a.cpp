#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1001;
const int maxx = 1e5+2;

int n, x;
int cost[maxn], pages[maxn];
int dp[maxx][maxn];

int main()
{
    scanf("%d %d",&n,&x);
    for (int i = 0; i < n; i++) scanf("%d",cost+i);
    for (int i = 0; i < n; i++) scanf("%d",pages+i);
    for (int i = 1; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            if (cost[j] <= i) {
                dp[i][j] = max(dp[i][j-1],dp[i-cost[j]][j-1]+pages[j]);
            }
            else {
                dp[i][j] = dp[i][j-1];
            }
        }
    }
    printf("%d\n",dp[x][n-1]);

    return 0;
}

