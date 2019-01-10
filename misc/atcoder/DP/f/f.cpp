#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3005;
string s, t;

int dp[maxn][maxn];
int f(int i, int j) {
    if (i == s.size() || j == t.size()) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    dp[i][j] = max(dp[i][j],max(f(i+1,j),f(i,j+1)));
    if (s[i] == t[j]) dp[i][j] = max(dp[i][j],1+f(i+1,j+1));
    return dp[i][j];
}

void retrieve(int i, int j) {
    if (i == s.size() || j == t.size()) return;
    if (dp[i][j] == 0) return;
    if (dp[i+1][j] == dp[i][j]) {
        retrieve(i+1,j);
        return;
    }   
    if (dp[i][j+1] == dp[i][j]) {
        retrieve(i,j+1);
        return;
    }
    cout << s[i];
    retrieve(i+1,j+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> t;
    memset(dp,-1,sizeof dp);
    f(0,0);
    /*
    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < t.size(); j++) {
            cout << f(i,j) << ' ';
        }
        cout << '\n';
    }
    */
    retrieve(0,0);
    cout << '\n';

    return 0;
}

