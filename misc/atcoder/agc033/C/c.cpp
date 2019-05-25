#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int N;
vector<int> adj[maxn];

int maxdist = 0, u = -1;
void DFS(int i, int d, int p) {
    if (d >= maxdist) {
        maxdist = d;
        u = i;
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        DFS(j,d+1,i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    DFS(1,0,1);
    DFS(u,0,u);
    int diam = maxdist;
    cout << (diam%3 == 1 ? "Second" : "First") << '\n';
}

