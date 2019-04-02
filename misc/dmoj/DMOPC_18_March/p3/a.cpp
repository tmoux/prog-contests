#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int N, M;
vector<int> adj[maxn];

pair<int,int> comp[maxn]; //nodes, edges;
bool seen[maxn];

set<pair<int,int>> s;

void DFS(int i, int c) {
    seen[i] = true;
    comp[c].first++;
    for (int j: adj[i]) {
        if (s.count({min(i,j),max(i,j)})) {
            s.erase({min(i,j),max(i,j)});
            comp[c].second++;
        }
        if (seen[j]) continue;
        DFS(j,c);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        s.insert({min(a,b),max(a,b)});
    }
    int pt = 0;
    for (int i = 1; i <= N; i++) {
        if (seen[i]) continue;
        DFS(i,pt);
        pt++;
    }
    /*
    for (int i = 0; i < pt; i++) {
        cout << comp[i].first << ' ' << comp[i].second << '\n';
    }
    */
    int nu = 0;
    for (int i = 0; i < pt; i++) {
        if (comp[i].first == comp[i].second + 1) continue;
        if (comp[i].first == comp[i].second) nu++;
        else {
            cout << "NO\n";
            return 0;
        }
    }
    cout << (nu <= 1 ? "YES" : "NO") << '\n';
}

