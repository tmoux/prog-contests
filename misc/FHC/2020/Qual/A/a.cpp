#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
int N;
int adj[maxn][maxn];
int ans[maxn][maxn];
void dfs(int i, int p) {
    ans[p][i] = 1;
    for (int j = 0; j < N; j++) {
        if (adj[i][j] && !ans[p][j]) {
            dfs(j,p);
        }
    }
}
void solve() {
    memset(adj,0,sizeof adj);
    memset(ans,0,sizeof ans);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            adj[i][j] = (abs(i-j) == 1);
        }
    }
    string s; cin >> s;
    for (int i = 0; i < N; i++) {
        if (s[i] == 'N') {
            for (int j = 0; j < N; j++) {
                adj[j][i] = 0;
            }
        }
    }
    cin >> s;
    for (int i = 0; i < N; i++) {
        if (s[i] == 'N') {
            for (int j = 0; j < N; j++) {
                adj[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        dfs(i,i);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (ans[i][j]?"Y":"N");
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int iter = 1; iter <= t; iter++) {
        cout << "Case #" << iter << ": \n";
        solve();
    }
}
