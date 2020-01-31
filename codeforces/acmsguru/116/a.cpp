#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool comp[10005];
int dp[10005];
int pre[10005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> primes;
    comp[1] = 1;
    for (int i = 2; i <= 10000; i++) {
        if (!comp[i]) {
            primes.push_back(i);
            for (int j = 2*i; j <= 10000; j += i) {
                comp[j] = true;
            }
        }
    }
    vector<int> sp;
    for (int i = 1; i <= primes.size(); i++) {
        if (!comp[i]) sp.push_back(primes[i-1]);
    }
    for (int i = 1; i <= 10000; i++) {
        dp[i] = 10000;
    }
    for (int i = 0; i <= 10000; i++) {
        if (dp[i] < 10000) {
            for (int p: sp) {
                if (i+p <= 10000) 
                    if (dp[i+p] > dp[i] + 1) {
                        dp[i+p] = dp[i] + 1;
                        pre[i+p] = p;
                    }
            }
        }
    }
    if (dp[n] == 10000) {
        cout << 0 << '\n';
        return 0;
    }
    cout << dp[n] << '\n';
    vector<int> ans;
    while (n > 0) {
        ans.push_back(pre[n]);
        n -= pre[n];
    }
    sort(ans.begin(),ans.end(),greater<int>());
    for (auto i: ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

