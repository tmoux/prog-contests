#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1001;
const int maxx = 1e5+2;

int n, x;
int dp[maxn][maxx];
pair<int,int> a[maxn];

void amax(int& a, int b) {
    a = max(a,b);
}

int main()
{
    scanf("%d %d",&n,&x);
    for (int i = 0; i < n; i++) scanf("%d",&a[i].first);
    for (int i = 0; i < n; i++) scanf("%d",&a[i].second);
    sort(a,a+n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= x; j++) {
            amax(dp[i][j],i==0?0:dp[i-1][j]);
        }
        for (int j = 0; j+a[i].first <= x; j++) {
            amax(dp[i][j+a[i].first],a[i].second+(i==0?0:dp[i-1][j]));
        }
    }
    int ans = 0;
    for (int j = 0; j <= x; j++) {
        amax(ans,dp[n-1][j]);
    }
    cout << ans << '\n';
    return 0;
}

