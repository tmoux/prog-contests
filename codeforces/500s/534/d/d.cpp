#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
vector<int> ret;
vector<int> adj[maxn];
void dfs(int level) {
    int sz = adj[level].size();
    if (sz == 0) {
        if (level < 3) return;
        dfs(level-3);
        return;
    }
    int y = adj[level].back();
    adj[level].pop_back();
    ret.push_back(y);
    dfs(level+1);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        adj[ai].push_back(i);
    }
    dfs(0);
    if (ret.size() != n) {
        cout << "Impossible\n";
    }
    else {
        cout << "Possible\n";
        for (auto i: ret) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

