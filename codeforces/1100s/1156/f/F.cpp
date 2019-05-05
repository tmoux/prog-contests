#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
const int maxn = 5005;
int n, m;

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

ll modInverse(ll x) {
    return modexp(x,M-2);
}

void madd(int& a, int b) {
    a = (a+b) % M;
}

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int dp[maxn][maxn]; //dp[i][j], i = prev selected, j = total # cards
map<int,int> mp;
vector<int> a;
int cnt[maxn];
int inverse[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    //precompute inverses
    for (int i = 0; i <= n; i++) {
        inverse[i] = modInverse(i);
    }
    //read input
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        if (!mp.count(ai)) a.push_back(ai);
        ++mp[ai];
    }
    a.push_back(0);
    cnt[0]++;
    sort(a.begin(),a.end());
    for (auto p: mp) {
        cnt[p.first] = p.second;
    }
    m = a.size();
    for (int j = 1; j <= n; j++) {
        //cout << j << endl;
        for (int i = 0; i < m; i++) {
            dp[j-1][i] = mult(dp[j-1][i],mult(cnt[a[i]],inverse[j]));
            if (i > 0) madd(dp[j-1][i],dp[j-1][i-1]);
        }
        for (int i = 0; i < m; i++) {
            int ai = a[i];
            dp[j][i] = mult(cnt[ai]-1,inverse[j]);
            madd(dp[j][i],(dp[j-1][m-1]-dp[j-1][i]+M)%M);
        }
    }
    int ans = dp[n][0];
    cout << ans << '\n';
    return 0;
}

