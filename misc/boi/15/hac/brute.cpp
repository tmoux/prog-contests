#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
const int INF = 2e9+9;
int n, v[maxn];

int dp[605][305][305]; //# plies

void amax(int& a, int b) {
    a = max(a,b);
}

void amin(int& a, int b) {
    a = min(a,b);
}

int f(int t, int i, int j) {
    if (dp[t][i][j] >= 0) return dp[t][i][j];
    int ir = (i+(t+1)/2) % n;
    int jr = (j+t/2) % n;
    //[i,ir], [j,jr]
    if (j == ((ir+1) % n) && (i == ((jr+1) % n))) {
        return dp[t][i][j] = 0;
    }
    if (t % 2 == 0) {
        //i's turn
        dp[t][i][j] = 0;
        if ((ir+1)% n != j) {
            amax(dp[t][i][j],f(t+1,i,j) + v[(ir+1)%n]);
        }
        else if ((i-1+n)%n != jr) {
            amax(dp[t][i][j],f(t+1,(i-1+n)%n,j) + v[(i-1+n)%n]);
        }
        if (t == 0) {
            dp[t][i][j] += v[i];
        }
        //printf("[%d, %d], [%d, %d]\n",i,ir,j,jr);
        //printf("[%d][%d][%d]: %d\n",t,i,j,dp[t][i][j]);
        return dp[t][i][j];
    }
    else {
        //j's turn
        dp[t][i][j] = INF;
        if ((jr+1) % n != i) {
            amin(dp[t][i][j],f(t+1,i,j));    
        }
        else if ((j-1+n)%n != ir) {
            amin(dp[t][i][j],f(t+1,i,(j-1+n)%n));
        }
        assert(dp[t][i][j] != INF);
        //printf("[%d, %d], [%d, %d]\n",i,ir,j,jr);
        //printf("[%d][%d][%d]: %d\n",t,i,j,dp[t][i][j]);
        return dp[t][i][j];
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> v[i];
    memset(dp,-1,sizeof dp);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int curr = INF;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            amin(curr,f(0,i,j));
        }
        //cout << i << ": " << curr << '\n';
        ans = max(ans,curr);
    }
    cout << ans << '\n';
}

