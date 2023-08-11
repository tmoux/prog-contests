#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n;
vector<int> adj[maxn];
int t[maxn];

void dfs(int i) {
    for (int j: adj[i]) {
        dfs(j);
        t[i] += t[j];
    }
}

vector<int> ans;
void dfs2(int i, int target) {
    for (int j: adj[i]) {
        int orig = t[j];
        dfs2(j,target);
        t[i] += (t[j]-orig);        
    }
    if (t[i] == target && ans.size() < 2) {
        ans.push_back(i);
        t[i] = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int rt = 0;
    for (int i = 1; i <= n; i++) {
        int par; cin >> par;
        int temp; cin >> temp;
        adj[par].push_back(i);
        t[i] = temp;
        if (par == 0) rt = i;
    }
    dfs(rt);
    int target = t[rt];
    if (target % 3 != 0) {
        cout << -1 << '\n';
        return 0;
    }
    target /= 3;
    dfs2(rt,target);
    if (ans.size() == 2 && ans[0] != rt && ans[1] != rt) {
        //cout << ans.size() << '\n';
        for (int i: ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    else {
        cout << -1 << '\n';
    }
}

