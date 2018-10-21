#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <cstring>
using namespace std;
typedef long long ll;

int n, m, k;
vector<vector<char>> grid;
vector<vector<int>> value;
ll ***dp;

int nxt(char c,  int j) {
    if (c == '|') {
        return j;
    }
    else if (c == '\\') {
        return j+1;
    }
    else return j - 1;
}

ll f(int i, int j, int k) {
    if (dp[k][i][j] >= 0) {
        return dp[k][i][j];
    }
    if (i == n || j == m || j == -1) {
        return 0;
    }
    if (i == n - 1) return dp[k][i][j] = value[i][j];
    
    if (grid[i][j] == '#') return dp[k][i][j] = 0;
    char chars[3] = {'|','\\','/'};
    dp[k][i][j] = 0;
    for (int a = 0; a < 3; a++) {
        if (chars[a] != grid[i][j]) {
            if (k > 0) {
                dp[k][i][j] = max(dp[k][i][j],value[i][j] + f(i+1,nxt(chars[a],j),k-1));
            }
        }
        else {
            dp[k][i][j] = max(dp[k][i][j],value[i][j] + f(i+1,nxt(chars[a],j),k));
        }

    }
    return dp[k][i][j];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    grid.reserve(n);
    for (int i = 0; i < n; i++) {
        grid.push_back(vector<char>(m));
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            grid[i][j] = s[j];
            //cout << grid[i][j];
        }
        //cout << '\n';
    }
    value.reserve(n);
    for (int i = 0; i < n; i++) {
        value.push_back(vector<int>(m));
        for (int j = 0; j < m; j++) {
            cin >> value[i][j];
        }
    }

    dp = new ll**[k+5]();
    for (int i = 0; i <= k; i++) {
        dp[i] = new ll*[n]();
        for (int j = 0; j < n; j++) {
            dp[i][j] = new ll[m]();
            for (int a = 0; a < m; a++) {
                dp[i][j][a] = -1;
            }
        }
    }
    
    
    ll ans = 0;
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        ans = max(ans,f(i,j,k));
        //cout << j << ' ' << f(0,j,k) << '\n';
    }
    }
    cout << ans << '\n';

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << dp[i][j][k] << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}
	

