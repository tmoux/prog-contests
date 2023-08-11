#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;
int p[maxn], q[maxn];

int in[maxn];
vector<int> dir[maxn], rev[maxn], condense[maxn];

bool visited[maxn];
int sz[maxn];
int comp[maxn];
deque<int> L;
void visit(int now) {
    if (!visited[now]) {
        visited[now] = true;
        for (int j: dir[now]) {
            visit(j);
        }
        L.push_front(now);
    }
}

void assign(int u, int root) {
    if (comp[u] == 0) {
        comp[u] = root;
        sz[root]++;
        for (int j: rev[u]) {
            assign(j,root);
        }
    }
}

int inn[maxn];
int ans[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> q[i];
    }
    for (int i = 1; i < n; i++) {
        in[p[i+1]]++;
        in[q[i+1]]++;
        dir[p[i]].push_back(p[i+1]);
        rev[p[i+1]].push_back(p[i]);
        dir[q[i]].push_back(q[i+1]);
        rev[q[i+1]].push_back(q[i]);
    }
    for (int i = 1; i <= n; i++) {
        visit(i);
    }
    for (int u: L) {
        assign(u,u);
    }
    set<int> verts;
    //create scc graph
    for (int i = 1; i <= n; i++) {
        verts.insert(comp[i]);
        //cout << i << ": " << comp[i] << '\n';
        for (int j: dir[i]) {
            if (comp[i] == comp[j]) continue;
            condense[comp[i]].push_back(comp[j]);
            inn[comp[j]]++;
        }
    }
    queue<int> q;
    for (int i: verts) {
        if (inn[i] == 0) q.push(i);
    }
    int pt = 0;
    while (!q.empty()) {
        int f = q.front(); q.pop();
        ans[f] = pt++;
        for (int j: condense[f]) {
            if (--inn[j] == 0) {
                q.push(j);
            }
        }
    }
    if (pt < k) {
        cout << "NO\n";
    }
    else {
        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << (char)(min(k-1,ans[comp[i]])+'a');
        }
        cout << '\n';
    }
}

