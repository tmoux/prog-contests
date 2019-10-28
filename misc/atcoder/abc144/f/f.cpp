#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 605;
int n, m;
vector<int> adj[maxn];
int deg[maxn];

vector<int> ord;
ld dp[maxn];

ld ans = 1e18;

void calcDP(int skip = n+1) {
    for (int i = 0; i < ord.size(); i++) {
        if (ord[i] == skip) continue;
        if (i == 0) dp[ord[i]] = 0;
        else {
            dp[ord[i]] = 1;
            int sz = adj[ord[i]].size();
            for (int j: adj[ord[i]]) {
                dp[ord[i]] += (ld)1/sz*dp[j];
            }
        }
        //cout << i << ": " << dp[ord[i]] << '\n';
    }
    ans = min(ans,dp[1]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        deg[b]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int f = q.front(); q.pop();
        ord.push_back(f);
        for (int j: adj[f]) {
            if (--deg[j] == 0) {
                q.push(j);
            }
        }
    }
    assert(ord.size() == n);
    reverse(ord.begin(),ord.end());    
    calcDP();
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() <= 1) continue;
        int sz = adj[i].size()-1;
        ld newDP = 1;
        ld mx = 0;
        for (int j: adj[i]) {
            newDP += dp[j]/sz;
            mx = max(mx,dp[j]);    
        }
        newDP -= mx/sz;
        ld orig = dp[i];
        dp[i] = newDP;
        calcDP(i);
        dp[i] = orig;
    }
    cout << fixed << setprecision(15) << ans << '\n';
}

