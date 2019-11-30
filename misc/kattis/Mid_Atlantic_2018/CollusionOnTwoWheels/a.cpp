#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e3+5;
struct pt
{
    int x, y;
};
int n;
pt v[maxn];
int adj[maxn][maxn];

int dist(pt a, pt b) {
    return abs(a.x-b.x) + abs(a.y-b.y);
}

void build(int d) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = dist(v[i],v[j]) > d;
        }
    }
}

int color[maxn];
bool poss;

void dfs(int i, int c) {
    if (!poss) return;
    color[i] = c;
    for (int j = 0; j < n; j++) {
        if (adj[i][j] && color[j] == color[i]) {
            poss = false;
            return;
        }
        else if (adj[i][j] && color[j] == -1) {
            dfs(j,1-c);
        }
    }
}

bool bipartite() {
    memset(color,-1,sizeof color);
    poss = true;
    for (int i = 0; i < n; i++) {
        if (color[i] != -1) continue;
        dfs(i,0);
    }
    return poss;
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y;
    }
    int lo = -1, hi = 5000;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        build(mid);
        if (bipartite()) {
            hi = mid;
        }
        else lo = mid;
    }
    cout << hi << '\n';
}
