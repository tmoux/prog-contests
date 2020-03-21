#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
vector<int> adj[maxn];

int color[maxn];
int c[2];
void dfs(int i) {
    ++c[color[i]];
    for (int j: adj[i]) {
        if (color[j] != -1) continue;
        color[j] = 1^color[i];
        dfs(j);
    }
}
vector<int> v[3];
int ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    memset(color,-1,sizeof color);
    color[1] = 0;
    dfs(1);
    int x = n/3;
    for (int i = 1; i <= n; i++) {
        v[i%3].push_back(i);
    }
    if (c[0] <= x) {
        for (int i = 1; i <= n; i++) {
            if (color[i] == 0) {
                ans[i] = v[0].back();
                v[0].pop_back();
            }
            else {
                if (!v[1].empty()) {
                    ans[i] = v[1].back();
                    v[1].pop_back();
                }
                else if (!v[2].empty()) {
                    ans[i] = v[2].back();
                    v[2].pop_back();
                }
                else {
                    ans[i] = v[0].back();
                    v[0].pop_back();
                }
            }
        }
    }
    else if (c[1] <= x) {
        for (int i = 1; i <= n; i++) {
            if (color[i] == 1) {
                ans[i] = v[0].back();
                v[0].pop_back();
            }
            else {
                if (!v[1].empty()) {
                    ans[i] = v[1].back();
                    v[1].pop_back();
                }
                else if (!v[2].empty()) {
                    ans[i] = v[2].back();
                    v[2].pop_back();
                }
                else {
                    ans[i] = v[0].back();
                    v[0].pop_back();
                }
            }
        }
    }
    else {
        for (int i = 1; i <= n; i++) {
            if (color[i] == 1) {
                if (!v[1].empty()) {
                    ans[i] = v[1].back();
                    v[1].pop_back();
                }
                else {
                    ans[i] = v[0].back();
                    v[0].pop_back();
                }
            }
            else {
                if (!v[2].empty()) {
                    ans[i] = v[2].back();
                    v[2].pop_back();
                }
                else {
                    ans[i] = v[0].back();
                    v[0].pop_back();
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
