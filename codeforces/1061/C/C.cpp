#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
const int M = 1e9+7;
int n, a[maxn];
int dp[maxn];

void add(int& a, int b) {
    a = (a+b) % M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        vector<int> facs;
        for (int j = 1; j*j <= x; j++) {
            if (x % j == 0) {
                facs.push_back(j);
                if (j*j != x) facs.push_back(x/j);
            }
        }
        sort(facs.begin(),facs.end(),greater<int>());
        for (int f: facs) {
            if (f > n) continue;
            add(dp[f],dp[f-1]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) add(ans,dp[i]);
    cout << ans << '\n';
   
    return 0;
}

