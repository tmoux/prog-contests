#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int a[maxn];
int d[maxn];
string s;
int n;
ll pre[maxn];

map<ll,int> mp[26];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 0; i < 26; i++) {
        cin >> a[i];
    }
    cin >> s;
    n = s.size();
    for (int i = 0; i < n; i++) {
        d[i] = s[i]-'a';
    }
    for (int i = 0; i < n; i++) {
        pre[i] = a[d[i]];
        if (i > 0) pre[i] += pre[i-1];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += mp[d[i]][i==0?0:pre[i-1]];
        mp[d[i]][pre[i]]++;
    }
    cout << ans << '\n';
}

