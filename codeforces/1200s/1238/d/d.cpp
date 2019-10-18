#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n;
string s;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    ll ans = 1LL*n*(n+1)/2;
    vector<int> v;
    int curr = 0;
    for (int i = 0; i < n; i++) {
        curr++;
        if (i == n-1 || s[i] != s[i+1]) {
            v.push_back(curr);
            curr = 0;
        }
    }
    for (int i = 0; i < v.size()-1; i++) {
        ans -= v[i]+v[i+1]-1;
    }
    ans -= n;
    cout << ans << '\n';
}

