#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, k;
vector<int> a;
ll g(int l, int r) {
    vector<int> b;
    for (int i = l; i <= r; i++) b.push_back(a[i]);
    sort(b.begin(),b.end(),greater<int>());
    ll res = 0;
    for (int i = 0; i < min(k,r-l+1); i++) {
        res += b[i];
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    string s; cin >> s;
    s += '#';
    char curr = s[0];
    int prev = 0;
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        if (s[i] != curr) {
            ans += g(prev,i-1);
            //cout << g(prev,i-1) << '\n';
            curr = s[i];
            prev = i;
        }
    }
    cout << ans << '\n';

    return 0;
}

