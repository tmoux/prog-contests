#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//pick some subsequence such that char in s is always paired with further
//char in t
const int maxn = 2005;
int n;
string s, t;
int dp[maxn][maxn];
int f(int i, int j) {
    int& res = dp[i][j];
    if (res != -1) return res;
    if (i == n || j == n) return res = 0;
    res = f(i+1,j);
    res = max(res,f(i,j+1));
    if (s[i] == t[j] && j >= i) res = max(res,1+f(i+1,j+1));
    return res;
}
void solve(int iter) {
    cin >> n >> s >> t;
    map<char,int> ms, mt;
    for (char c: s) ms[c]++;
    for (char c: t) mt[c]++;
    for (auto p: ms) {
        if (mt[p.first] != p.second) {
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    int ans = n-f(0,0);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int iter = 1; iter <= t; iter++) {
        solve(iter);
    }
}
