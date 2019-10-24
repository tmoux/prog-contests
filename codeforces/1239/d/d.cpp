#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1000005;
const int INF = 2000000000;
vector<int> inn[maxn], out[maxn];
vector<int> condense[maxn], rev[maxn];
int deg[maxn]; //degree of scc
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

map<int,vector<int>> mp;
void assign(int u, int root) {
    if (comp[u] == 0) {
        comp[u] = root;
        mp[root].push_back(u);
        sz[root]++;
        for (int j: out[u]) {
            assign(j,root);
        }
    }
}

int n, m;

void pr(vector<int> v) {
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            inn[i].clear();
            out[i].clear();
            condense[i].clear();
            rev[i].clear();
            L.clear();
            visited[i] = 0;
            sz[i] = 0;
            comp[i] = 0;
            deg[i] = 0;
            mp.clear();
        }
        for (int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            inn[a].push_back(b);
            out[b].push_back(a);
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
        for (int i = 1; i <= n; i++) {
            //cout << comp[i] << ": " << deg[comp[i]] << '\n';
        }
        if (mp.size() == 1) {
            cout << "No\n";
        }
        else {
            /*
            for (auto p: mp) {
                pr(p.second);
            }
            */
            cout << "Yes\n";
            vector<int> v;
            int c = -1;
            for (auto it = mp.begin(); it != mp.end(); ++it) {
                //cout << it->first << ": " << deg[it->first] << '\n';
                if (deg[it->first] == 0) {
                    v = it->second;
                    c = it->first;
                    break;
                }
            }
            vector<int> u;
            //cout << "sz = " << mp.size() << '\n';
            for (auto p: mp) {
                if (p.first == c) continue;
                for (int i: p.second) {
                    u.push_back(i);
                }
            }
            cout << v.size() << ' ' << u.size() << '\n';
            pr(v);
            pr(u);
        }
    }
}

