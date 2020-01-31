#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, x, y;
vector<int> adj[maxn];
int deg[maxn];

int dp1[maxn], dp2[maxn];
void dfs(int i, int p) {
    int sum_dp2 = 0;
    vector<int> diffs;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
        sum_dp2 += dp2[j];
        diffs.push_back(dp1[j]-dp2[j]);
    }
    sort(diffs.begin(),diffs.end());
    int mindiff_dp1 = 1;
    if (diffs.size() >= 1) mindiff_dp1 = min(mindiff_dp1,diffs[0]);
    dp1[i] = mindiff_dp1 + sum_dp2;

    dp2[i] = dp1[i];
    if (diffs.size() >= 2) {
        dp2[i] = min(dp2[i],sum_dp2+diffs[0]+diffs[1]-1);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> x >> y;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }
    if (x == y) {
        cout << (1LL*(n-1)*x) << endl;
    }
    else if (x > y) {
        int maxDeg = 0;
        for (int i = 1; i <= n; i++) {
            maxDeg = max(maxDeg,deg[i]);
        }
        if (maxDeg == n-1) {
            cout << (1LL*(n-2)*y + x) << endl;
        }
        else {
            cout << (1LL*(n-1)*y) << endl;
        }
    }
    else {
        dfs(1,1);
        int paths = dp2[1];
        //cout << "paths = " << paths << endl;
        cout << (1LL*(paths-1)*y + 1LL*(n-paths)*x) << endl;
    }
}

