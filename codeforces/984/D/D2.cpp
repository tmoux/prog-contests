#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int dp[maxn][maxn];
int maxR[maxn][maxn];
int n;
int A[maxn];

int f(int l, int r) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r) return dp[l][r] = A[l];
    return dp[l][r] = f(l+1,r) ^ f(l,r-1);
}

int g(int l, int r) {
    if (maxR[l][r] != -1) return maxR[l][r];
    if (l == r) return maxR[l][r] = f(l,r);
    return maxR[l][r] = max(max(f(l,r),g(l+1,r)),g(l,r-1));
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1,sizeof(dp));
    memset(maxR,-1,sizeof(maxR));
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << g(l,r) << '\n';
    }

    return 0;
}
	

