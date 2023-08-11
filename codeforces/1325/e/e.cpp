#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x), end(x)

const int maxn = 1e5+5, maxx = 1e6+6;
int n, a[maxn];
vector<int> p[maxn];

void factor(int i) {
    int x = a[i];
    for (int j = 2; j*j <= a[i]; j++) {
        if (x % j == 0) {
            int cnt = 0;
            while (x % j == 0) {
                cnt ^= 1;
                x /= j;
            }
            if (cnt) p[i].push_back(j);
        }
    }
    if (x > 1) {
        p[i].push_back(x);
    }
}

vector<int> adj[maxx];

int dist[maxx], par[maxx];

void get_unique(vector<int>& v) {
    sort(all(v));
    v.erase(unique(all(v)),v.end());
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> nodes;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        factor(i);
        if (p[i].empty()) {
            cout << 1 << '\n';
            return 0;
        }
        else if (p[i].size() == 1) {
            adj[p[i][0]].push_back(1);
            adj[1].push_back(p[i][0]);
            nodes.push_back(1);
            nodes.push_back(p[i][0]);
        }
        else {
            assert(p[i].size() == 2);
            adj[p[i][0]].push_back(p[i][1]);
            adj[p[i][1]].push_back(p[i][0]);
            nodes.push_back(p[i][0]);
            nodes.push_back(p[i][1]);
        }
    }
    get_unique(nodes);
    //multi-edge --> cycle of length 2
    for (int i: nodes) {
        int sz = adj[i].size();
        get_unique(adj[i]);
        if (sz > adj[i].size()) {
            cout << 2 << '\n';
            return 0;
        }
    }
    int ans = maxn;
    for (int i: nodes) {
        if (i > 1000) continue;
        for (int j: nodes) {
            dist[j] = maxx;
            par[j] = -1;
        }
        queue<int> q;
        dist[i] = 0;
        q.push(i);
        while (!q.empty()) {
            int f = q.front(); q.pop();
            for (auto j: adj[f]) {
                if (dist[j] > dist[f] + 1) {
                    dist[j] = dist[f] + 1;
                    par[j] = f;
                    q.push(j);
                }
                else if (par[f] != j && par[j] != f) {
                    ans = min(ans,dist[f]+dist[j]+1);
                }
            }
        }
    }
    cout << (ans == maxn ? -1 : ans) << '\n';
}
