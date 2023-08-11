#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, z;
int x[maxn];

int dp[maxn];
int f(int i) {
    if (dp[i] != -1) return dp[i];
    if (i >= n) return dp[i] = 0;
    dp[i] = f(i+1);
    if (x[i+1] - x[i] <= z) {
        dp[i] = max(dp[i],2+f(i+2));
    }
    return dp[i];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> z;
    for (int i = 0; i < n; i++) cin >> x[i];
    sort(x,x+n);
    int i = 0, j = n/2;
    int pairs = 0;
    for (; i < n/2; i++) {
        while (j < n && x[j]-x[i] < z) j++;
        if (x[j]-x[i] >= z) pairs++;
    }
    cout << pairs << '\n';


    return 0;
}
