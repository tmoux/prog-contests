#include <bits/stdc++.h>
using namespace std;

int n, c[200005], ans[200005];
vector<int> adj[200005];

void merge(set<int>& a, set<int>& b) {
    if (a.size() < b.size()) swap(a,b);
    for (auto i: b) {
        a.insert(i);
    }
}

set<int>* dfs(int i, int p) {
    set<int> *ni = new set<int>;
    ni->insert(c[i]);
    for (int j: adj[i]) {
        if (j != p) merge(*ni,*dfs(j,i));
    }
    ans[i] = ni->size();
    return ni;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " \n"[i==n];
}
