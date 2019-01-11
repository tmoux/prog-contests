#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, a[maxn];
vector<int> primes[maxn];
map<int,int> dp[maxn];
vector<int> adj[maxn];

int ans = 0;
void dfs(int i, int p) {
    for (int pr: primes[a[i]]) {
        dp[i][pr] = 0;
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
        for (int pr: primes[a[i]]) {
            if (!dp[j].count(pr)) continue;
            ans = max(ans,dp[i][pr] + dp[j][pr] + 1);        
        }
        for (int pr: primes[a[i]]) {
            if (!dp[j].count(pr)) continue;
            dp[i][pr] = max(dp[i][pr],dp[j][pr] + 1);   
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mx = max(mx,a[i]);
        if (primes[a[i]].empty()) {
            int ai = a[i];
            for (int j = 2; j*j <= a[i]; j++) {
                if (ai % j == 0) {
                    primes[a[i]].push_back(j);
                    while (ai % j == 0) ai /= j;
                }
            }
            if (ai > 1) primes[a[i]].push_back(ai);
        }
    }
    if (mx == 1) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1,1);        
    cout << (ans+1) << '\n';

    return 0;
}

