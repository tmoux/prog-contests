#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n;
int a[maxn];

int dp[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    set<int> s;
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s.insert(a[i]);
    }
    int pt = 0;
    for (auto i: s) {
        mp[i] = pt++;
    }
    for (int i = 0; i < n; i++) {
        a[i] = mp[a[i]];
    }

    dp[0] = 0;
    int min_height = a[0];
    set<pair<int,int>> highs;
    for (int i = 1; i < n; i++) {
        dp[i] = dp[i-1] + 1;
        
    }
    cout << dp[n-1] << '\n';
}
