#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a,a+n);
    ll res = 0;
    //turn all to 1's
    for (int i = 0; i < n; i++) {
        res += abs(1-a[i]);
    }
    ll ans = res;
    for (int i = 0; i + 1 < n; i += 2) {
        res -= abs(1-a[i]);
        res -= abs(1-a[i+1]);
        res += abs(-1-a[i]);
        res += abs(-1-a[i+1]);
        ans = min(ans,res);
    }
    cout << ans << '\n';
}

