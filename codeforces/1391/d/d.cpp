#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int diff(vector<int> a, vector<int> b) {
    int ret = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) ret++;
    }
    return ret;
}

int n, m;
vector<vector<int>> a;
int dp[8][maxn];

bool checkOdd(int s1, int s2) {
    int a0 = s1&1;
    int a1 = (s1/2)&1;
    int a2 = (s1/4)&1;

    int b0 = s2&1;
    int b1 = (s2/2)&1;
    int b2 = (s2/4)&1;

    return (((a0^a1^b0^b1) == 1) && ((a1^a2^b1^b2) == 1));
}
int getDiff(int s, int i) {
    int a0 = s&1;
    int a1 = (s/2)&1;
    int a2 = (s/4)&1;

    return (a0 != a[0][i]) + (a1 != a[1][i]) + (a2 != a[2][i]);
}
//state = previous state
int f(int state, int i) {
    int& res = dp[state][i];
    if (res != -1) return res;
    if (i == m) return res = 0;
    res = 2e9;
    for (int s = 0; s < 8; s++) {
        if (i == 0 || checkOdd(state,s)) {
            res = min(res,getDiff(s,i)+f(s,i+1));
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    a.resize(n,vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            a[i][j] = c-'0';
        }
    }
    if (n == 1) {
        cout << 0 << '\n';
    }
    else if (n == 2) {
        vector<int> sum(m);
        for (int j = 0; j < m; j++) {
            sum[j] = a[0][j]^a[1][j];
        }
        vector<int> t1(m), t2(m);
        for (int j = 0; j < m; j++) {
            t1[j] = j % 2 == 0 ? 0 : 1;
            t2[j] = j % 2 == 0 ? 1 : 0;
        }
        cout << min(diff(sum,t1),diff(sum,t2)) << '\n';
    }
    else if (n == 3) {
       memset(dp,-1,sizeof dp); 
       int ans = f(0,0);
       cout << ans << '\n';
    }
    else {
        cout << -1 << '\n';
    }
}
