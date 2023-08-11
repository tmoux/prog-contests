#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n;
vector<int> adj[maxn];
int len[maxn];
int sz[maxn]; //sz is length of single segment, len is total subtree
pair<int,int> ans[maxn];

void dfs(int i, int p) {
    len[i] = 2;
    sz[i] = 2;
    int add = 1;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
        len[i] += len[j];
        sz[i]++;

        len[j] += add;
        sz[j] += add;

        add = len[j];
    }
}

void recover(int i, int p) {
    int off = -1;
    for (int j: adj[i]) {
        if (j == p) continue;
        ans[j].first = ans[i].second+off;
        off--;
        ans[j].second = ans[j].first+sz[j]-1;
        recover(j,i);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1,1);
    ans[1] = {1,sz[1]};
    recover(1,1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i].first << ' ' << ans[i].second << '\n';
    }
}

