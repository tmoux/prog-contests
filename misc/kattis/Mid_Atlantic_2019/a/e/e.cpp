#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using MP = map<int,pair<int,int>>;
//Never jump down--mid atlantic regional 2019 (E)

const int maxn = 1e6+6, M = 11092019;
int n, u[maxn];
vector<int> adj[maxn];

void merge(MP& a, MP& b) {
    if (a.size() < b.size()) swap(a,b);
    for (auto p: b) {

    }
}

MP* dfs(int i) { //(len, # ways)
    MP *mp = new MP;
    for (int j: adj[i]) {
        merge(*mp,*dfs(j));
    }
    return mp;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> u[i];
    for (int i = 2; i <= n; i++) {
        int pi; cin >> pi;
        adj[pi].push_back(i);
    }
    auto ans = dfs(1);
}

