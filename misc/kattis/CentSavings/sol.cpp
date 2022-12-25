#include <bits/stdc++.h>
 
using namespace std;

const int maxn = 2050, maxd = 25;
int p[maxn];
int dp[maxn][maxd];

int N, D;

int round(int x) {
    if (x % 10 < 5) return x - (x % 10);
    else return x - (x % 10) + 10;
}

int f(int i, int d) {
    int& res = dp[i][d];
    if (res != -1) return res;
    res = round(p[i]);
    if (d > 0) {
        for (int j = 0; j < i; j++) {
            res = min(res, round(p[i] - p[j]) + f(j, d-1));
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> D;
    for (int i = 0; i < N; i++) {
        cin >> p[i];
        if (i > 0) p[i] += p[i-1];
    }
    memset(dp, -1, sizeof dp);
    cout << f(N-1, D) << '\n'; 
}
