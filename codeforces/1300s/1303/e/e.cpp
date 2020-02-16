#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 405;
string S, T;

int dp[maxn][maxn];

void amax(int& a, int b) {
    a = max(a,b);
}

void solve() {
    cin >> S >> T;
    //check if subseq
    int pt = 0;
    for (int i = 0; i < S.size(); i++) {
        if (pt < T.size() && S[i] == T[pt]) {
            pt++;
        }
    }
    if (pt == T.size()) {
        cout << "YES\n";
        return;
    }
    for (int u1 = 1, u2 = T.size()-1; u1 < T.size(); u1++, u2--) {
        string u = T.substr(0,u1);
        string v = T.substr(u1);
        for (int j = 0; j <= u1; j++) {
            if (j == 0) {
                dp[0][j] = S[0] == v[0] ? 1 : 0;
            }
            else if (j == 1) {
                dp[0][j] = S[0] == u[0] ? 0 : -1;
            }
            else dp[0][j] = -1;
        }
        for (int i = 1; i < S.size(); i++) {
            for (int j = 0; j <= u1; j++) {
                dp[i][j] = dp[i-1][j];
                if (dp[i-1][j] != -1 && dp[i-1][j] < v.size() && S[i] == v[dp[i-1][j]]) {
                    amax(dp[i][j],dp[i-1][j]+1);
                }
                if (j > 0 && S[i] == u[j-1]) {
                    amax(dp[i][j],dp[i-1][j-1]);
                }
            }
        }
        if (dp[S.size()-1][u1] == u2) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

