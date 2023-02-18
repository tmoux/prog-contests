#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, INF = 2e9+9;
int m, Q;

int dp[10000005];
int mxmod[20000005];

vector<int> primes;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> m >> Q;
    for (int i = 0; i < m; i++) {
        int p; cin >> p;
        primes.push_back(p);
    }
    sort(primes.begin(),primes.end());
    int maxPrime = primes.back();
    for (int i = 1; i < maxPrime; i++) {
        dp[i] = 1;
    }

    for (int p: primes) {
        for (int i = p; i <= 20000000; i += p) {
            mxmod[i-1] = max(mxmod[i-1],p-1);
        }
    }

    for (int i = 20000000; i >= 1; i--) {
        mxmod[i] = max(mxmod[i],mxmod[i+1]-1);
    }

    for (int i = maxPrime; i <= 10000000; i++) {
        dp[i] = INF;
        dp[i] = min(dp[i],1+dp[i-mxmod[i]]);
    }

    /*
    for (int i = 1; i <= 500; i++) {
        cout << i << ": " << dp[i] << '\n';
    }
    */

    /*
    for (int i = 1; i <= 100; i++) {
        int mx = 0;
        for (int j: primes) {
            mx = max(mx,i%j);
        }
        cout << i << ": " << mxmod[i] << ' ' << mx << '\n';
    }
    */

    while (Q--) {
        int qi; cin >> qi;
        if (dp[qi] == INF) cout << "oo\n";
        else cout << dp[qi] << '\n';
    }
}

