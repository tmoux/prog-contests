#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 13;
int n, m, v;
vector<int> adj[maxn];

int dp[maxn][4000];

void markAll(int v, int color, int* seen, int mask) {
    seen[v] = color;
    for (int j: adj[v]) {
        if (!(mask & 1 << j) && seen[j] != color)  {
            markAll(j,color,seen,mask);    
        }
    }
}

int factorial(int x) {
    if (x == 0) return 1;
    int ret = 1;
    for (int i = 2; i <= x; i++) {
        ret *= i;
    }
    return ret;
}

int f(int v, int mask) {
    if (dp[v][mask] >= 0) return dp[v][mask];
    int seen[maxn];
    memset(seen,0,sizeof(seen));
    int numways[maxn];
    memset(numways,0,sizeof(numways));
    int curr = 1;
    for (int j: adj[v]) {
        if (!(mask & (1 << j))) {
            if (seen[j] == 0) {
                markAll(j,curr++,seen,mask | (1 << v));
            }
            int col = seen[j];
            numways[col] += f(j,mask | (1 << v));
        }
    }

    int ret = 1;
    int numsubs = 0;
    for (int i = 1; i < maxn; i++) {
        if (numways[i] > 0) { 
            ret *= numways[i];
            numsubs++;
        }
    }
    return dp[v][mask] = ret*factorial(numsubs);
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> v;
    v--;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    memset(dp,-1,sizeof(dp));
    int ans = f(v,0); 
    cout << ans << '\n';

    return 0;
}
	

