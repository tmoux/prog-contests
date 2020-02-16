#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e3+3;
int N;
int a[maxn][maxn];

struct Edge
{
    int to, wt;
};

int color[2*maxn];
vector<Edge> adj[2*maxn];
bool poss = true;

void dfs(int i, int c) {
    color[i] = c;
    for (Edge e: adj[i]) {
        int nx = c^e.wt;
        if (color[e.to] == -1) {
            dfs(e.to,nx);
        }
        else if (color[e.to] == nx) continue; 
        else {
            poss = false;
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> a[i][j];
            if (a[i][j]) {
                adj[i].push_back({j+N,1});
                adj[j+N].push_back({i,1});
            }
            else {
                adj[i].push_back({j+N,0});
                adj[j+N].push_back({i,0});
            }
        }
    }
    memset(color,-1,sizeof color);
    for (int i = 0; i < 2*N; i++) {
        if (color[i] == -1) dfs(i,0);
    }
    if (!poss) {
        cout << -1 << '\n';
    }
    else {
        vector<pair<char,int>> v;
        for (int i = 0; i < N; i++) {
            if (color[i] == 1) {
                v.push_back({'R',i+1});
            }
        }
        for (int i = N; i < 2*N; i++) {
            if (color[i] == 1) {
                v.push_back({'C',i-N+1});
            }
        }
        cout << v.size() << '\n';
        for (auto p: v) {
            cout << p.first << ' ' << p.second << '\n';
        }
    }
}

