#include <bits/stdc++.h>
using namespace std;

const int maxn = 105, INF = 987654321;
int n;
pair<int,int> A[maxn];
map<int,int> dp[maxn];

int f(int i, int b) {
    if (dp[i].find(b) != dp[i].end()) return dp[i][b];
    if (i == n) {
        if (b >= 0) return dp[i][b] = 0;
        else return dp[i][b] = INF;
    }
    return dp[i][b] = min(f(i+1,b-A[i].second),A[i].first+f(i+1,b+A[i].first));
}

int main()
{
    scanf("%d",&n);
    for (int i = 0; i < n; i++) 
        scanf("%d %d",&A[i].first,&A[i].second);
    printf("%d\n",f(0,0));
    return 0;
}
	

