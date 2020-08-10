#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<int,int> ask(vector<int> v) {
    cout << "? " << v.size() << ' ';
    for (auto i: v) {
        cout << i << ' ';
    }
    cout << endl;
    int x, d; cin >> x >> d;
    assert(x != -1);
    return make_pair(x,d);
}

void answer(int a, int b) {
    cout << "! " << a << ' ' << b << endl;
    string s; cin >> s;
    assert(s == "Correct");
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }
    pair<int,int> ans = ask(v);
    int d = ans.second;
    int x = ans.first;
    set<int> nodes = {x};
    for (int i = 9; i >= 0; i--) {
        int dist = 1<<i;
        queue<int> q;
        vector<int> dd(n+1,n+5);
        vector<int> query;
        for (auto j: nodes) {
            q.push(j);
            dd[j] = 0;
        }
        while (!q.empty()) {
            int f = q.front(); q.pop();
            if (dd[f] >= dist) {
                query.push_back(f);
            }
            for (auto j: adj[f]) {
                if (dd[j] > dd[f] + 1) {
                    dd[j] = dd[f] + 1;
                    q.push(j);
                }
            }
        }
        if (query.empty()) continue;
        auto p = ask(query);
        if (p.second > d) continue;
        else {
            int add = p.first;
            vector<int> par(n+1,-1);
            queue<int> q;
            q.push(add);
            par[add] = add;
            while (!q.empty()) {
                int f = q.front(); q.pop();
                if (nodes.count(f)) {
                    while (true) {
                        f = par[f];
                        nodes.insert(f);
                        if (f == add) break;
                    }
                    break;
                }
                for (int j: adj[f]) {
                    if (par[j] == -1) {
                        par[j] = f;
                        q.push(j);
                    }
                }
            }
        }
    }
    /*
    cout << "nodes found:\n";
    for (auto j: nodes) {
        cout << j << '\n';
    }
    */
    vector<int> deg(n+1,0);
    for (auto j: nodes) {
        for (int k: adj[j]) {
            deg[k]++;
        }
    }
    vector<int> ret;
    for (int j: nodes) if (deg[j] == 1) ret.push_back(j);
    assert(ret.size() == 2);
    answer(ret[0],ret[1]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
