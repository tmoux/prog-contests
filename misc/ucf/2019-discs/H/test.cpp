#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3005;
int n;

bool adj[maxn][maxn];
bool seen[maxn];

void dfs(int i) {
    for (int j = 0; j < n; j++) {
        if (!seen[j] && adj[i][j]) {
            seen[j] = true;
            dfs(j);
        }
    }
}

int count(int mask) {
    memset(adj,0,sizeof adj);
    memset(seen,0,sizeof seen);
    int t = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (mask&(1<<t)) {
                adj[i][j] = adj[j][i] = true;
            }
            t++;
        }
    }
    int comp = 0;
    for (int i = 0; i < n; i++) {
        if (!seen[i]) {
            dfs(i);
            comp++;
        }
    }
    return comp;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int ch2 = n*(n-1)/2;
    ll ans = 0;
    for (int i = 0; i < (1<<ch2); i++) {
        ans += count(i);        
    }
    cout << n << ": " << ans << '\n';
}

