#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
vector<int> adj[maxn];
random_device device;
mt19937 gen(device());
int target;

int color[maxn];
int par[maxn];
void dfs(int i, int p) {
    if (color[i] == 2) return;
    if (color[i] == 1) {
        int cur = p;
        vector<int> cyc;
        cyc.push_back(i);
        while (cur != i) {
            cyc.push_back(cur);
            cur = par[cur];
        }
        if (cyc.size() >= target) {
            cout << 2 << '\n';
            cout << cyc.size() << '\n';
            for (auto j: cyc) {
                cout << j << ' ';
            }
            cout << '\n';
            exit(0);
        }
        return;
    }

    par[i] = p;
    color[i] = 1;

    for (int j: adj[i]) {
        if (j == par[i]) continue;
        dfs(j,i);
    }
    color[i] = 2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    target = 1;
    while (target*target < n) target++;
    vector<int> p;
    for (int i = 1; i <= n; i++) {
        p.push_back(i);
    }
    for (int _ = 0; _ < 500; _++) {
        shuffle(p.begin(),p.end(),gen);
        vector<bool> seen(n+1,false);
        vector<int> is;
        for (int i: p) {
            if (!seen[i]) {
                is.push_back(i);
                seen[i] = true;
                for (int j: adj[i]) {
                    seen[j] = true;
                }
                if (is.size() == target) {
                    cout << 1 << '\n';
                    for (auto i: is) {
                        cout << i << ' ';
                    }
                    cout << '\n';
                    exit(0);
                }
            }
        }
    }
    //find cycle
    dfs(1,0);
    assert(false);
}
