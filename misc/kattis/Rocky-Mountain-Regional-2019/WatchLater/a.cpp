#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 405;
int n, k;
string s;
int pt = 0;
int a[maxn];
int dp[1<<20];
int last[20];

int f(int mask) {
    if (mask+1 == (1<<pt)) return 0;
    if (dp[mask] >= 0) return dp[mask];
    int res = maxn;
    for (int i = 0; i < pt; i++) {
        if (mask & (1<<i)) continue;
        
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    cin >> s;
    map<char,int> mp;
    for (char c: s) {
        if (mp.count(c)) continue;
        mp[c] = pt++;
    }
    for (int i = 0; i < n; i++) {
        a[i] = mp[s[i]];
        last[a[i]] = i;
    }
    memset(dp,-1,sizeof dp);
    int ans = f(0);

}

