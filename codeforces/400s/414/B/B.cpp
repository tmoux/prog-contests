#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005, M = 1e9+7;
int n, k;
vector<int> divs[maxn];        
int dp[maxn][maxn];
void madd(int& a, int b) {
    a = (a+b) % M;
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j*j <= i; j++) {
            if (i % j == 0) {
                divs[i].push_back(j);
                if (i/j != j) {
                    divs[i].push_back(i/j);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) dp[1][i] = 1;
    for (int i = 2; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k: divs[j]) {
                madd(dp[i][j],dp[i-1][k]);
            }
        }
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) madd(sum,dp[k][i]);
    cout << sum << '\n';

    return 0;
}

