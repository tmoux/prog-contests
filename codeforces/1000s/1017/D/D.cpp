#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxq = 5e5+5;
const int maxn = 13;
int n, m, q;
int val[maxn];
int numUnder[1 << maxn][103];
int mp[1 << 12];
bool vis[1 << 12];
int dp[1 << 12][101];

inline int getnum(string& s) {
    int res = 0;
    for (int j = 0; j < n; j++) {
        int a = s[n-1-j]-'0';
        res |= (a << j);
    }
    return res;
}

void solve(int mask) {
    vis[mask] = true;
    for (int i = 0; i < (1 << n); i++) {
        if (mp[i] != 0) {
            int tot = 0;
            for (int k = 0; k < n; k++) {
                bool a = mask & (1 << (n-1-k));
                bool b = i & (1 << (n-1-k));
                if (a == b) {
                    tot += val[k];
                }
                if (tot > 100) break;
            }
            if (tot <= 100) {
                dp[mask][tot] += mp[i];
            }
        }
    }
    for (int i = 1; i <= 100; i++) {
        dp[mask][i] += dp[mask][i-1];
    }
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); 
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        int as = getnum(s);
        mp[as]++;
    }
    
    for (int i = 0; i < q; i++) {
        string t; int k; cin >> t >> k;
        int mask = getnum(t);
        if (!vis[mask]) {
            solve(mask);
        }
        cout << dp[mask][k] << '\n';
    }

    return 0;
}
	

