#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//calculate minimum nonempty subset S of nodes
//such that for every client (u,n1) in S, either (u,u2) is in S,
//or h[n1]-1 != h[h2]

const int maxn = 1e5+5;
int n, m, h;
int u[maxn];

vector<int> inn[maxn], out[maxn];
vector<int> condense[maxn], rev[maxn];
bool visited[maxn];
int sz[maxn];
int comp[maxn];
deque<int> L;

void visit(int now) {
    if (!visited[now]) {
        visited[now] = true;
        for (int j: inn[now]) {
            visit(j);
        }
        L.push_front(now);
    }
}

void assign(int u, int root) {
    if (comp[u] == 0) {
        comp[u] = root;
        sz[root]++;
        for (int j: out[u]) {
            assign(j,root);
        }
    }
}

int deg[maxn]; //degree of scc components

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> h;
    for (int i = 1; i <= n; i++) {
        cin >> u[i];
    }
    for (int i = 0; i < m; i++) {
        int c1, c2; cin >> c1 >> c2;
        if ((u[c1]+1)%h == u[c2]) {
            inn[c1].push_back(c2);
            out[c2].push_back(c1);
        }
        if ((u[c2]+1)%h == u[c1]) {
            inn[c2].push_back(c1);
            out[c1].push_back(c2);
        }
    }
    //Kosaraju
    for (int i = 1; i <= n; i++) {
        visit(i);
    }
    for (int u: L) {
        assign(u,u);
    }
    for (int i = 1; i <= n; i++) {
        for (int j: inn[i]) {
            if (comp[i] == comp[j]) continue;
            deg[comp[i]]++;
        }
    }
    pair<int,int> mn = {maxn,-1};
    for (int i = 1; i <= n; i++) {
        if (deg[comp[i]] > 0) continue;
        mn = min(mn,{sz[comp[i]],comp[i]});
    }
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (comp[i] == mn.second) ans.push_back(i);
    }
    //output
    cout << mn.first << '\n';
    for (auto i: ans) {
        cout << i << ' ';
    }
    cout << '\n';


    return 0;
}

