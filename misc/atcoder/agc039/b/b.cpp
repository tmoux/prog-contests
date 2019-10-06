#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 205;
int N;
int adj[maxn][maxn];

int color[maxn];

bool stop = false;
void fill(int i, int c) {
    if (stop) {
        return;
    }
    color[i] = c;
    for (int j = 0; j < N; j++) {
        if (adj[i][j]) {
            if (color[j] != -1 && (c&1) == (color[j]&1)) {
                stop = true;
                return;
            }
            else if (color[j] == -1) {
                fill(j,c+1);
            }
        }
    }
}

int main() {
    cin >> N;
    int m = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char c; cin >> c;
            adj[i][j] = c-'0';
            if (adj[i][j] == 1) m++;
        }
    }
    //look for odd cycles
    //and fill in bipartite at the same time
    int res = 0;
    for (int j = 0; j < N; j++) {
        memset(color,-1,sizeof color);
        queue<int> q;
        q.push(j);
        color[j] = 0;
        while (!q.empty()) {
            int f = q.front(); q.pop();
            for (int k = 0; k < N; k++) {
                if (adj[f][k]) {
                    if (color[k] != -1 && (color[f]&1) == (color[k]&1)) {
                        cout << -1 << '\n';
                        exit(0);
                    }
                    else if (color[k] == -1) {
                        color[k] = color[f] + 1;
                        q.push(k);
                    }
                }
            }        
        }
        int ans = 0;
        for (int i = 0; i < N; i++) {
            ans = max(ans,color[i]);
        }
        /*
        cout << j << ": " << ans << '\n';
        for (int i = 0; i < N; i++) {
            cout << i << ":: " << color[i] << '\n';
        }
        */
        res = max(res,ans);
    }
    cout << (res+1) << '\n'; 
}
