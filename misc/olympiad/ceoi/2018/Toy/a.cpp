#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
map<int,int> prime;

void factor(int n) {
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
               prime[i]++;
               n /= i;
            }
            factor(n);
            return;
        }
    }
    if (n > 1) {
        prime[n]++;
    }
}

const int maxn = 7005;
int dp[maxn][maxn];

int f(int mn, int i) {
    if (i == 0) return 1;
    if (mn > i) return 0;
    if (dp[mn][i] != -1) return dp[mn][i];
    return dp[mn][i] = f(mn+1,i) + f(mn,i-mn);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    factor(n);
    memset(dp,-1,sizeof dp);
    for (auto p: prime) {
        int ex = p.second;

    }
}

