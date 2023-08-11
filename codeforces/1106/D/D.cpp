#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
vector<int> adj[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    set<int> curr;
    vector<int> ans;
    vector<bool> used(n+1);
    curr.insert(1);
    for (int i: adj[1]) {
        curr.insert(i);
    }
    used[1] = true;
    while (!curr.empty()) {
        int f = *curr.begin();
        //cout << f << '\n';
        used[f] = true;
        curr.erase(curr.begin());
        ans.push_back(f);
        for (int i: adj[f]) {
            if (!used[i]) {
                used[i] = true;
                curr.insert(i);
            }
        }
    }

    for (int i: ans) {
        cout << i << ' ';
    }

    return 0;
}

