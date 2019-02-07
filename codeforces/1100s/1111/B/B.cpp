#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, k, m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> m;
    vector<int> a(n+1);
    vector<ll> pre(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(next(a.begin()),a.end());
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i-1] + a[i];
    }
    double ans = 0.0;
    for (int i = 0; i <= min(n-1,m); i++) {
        int x = n - i;
        double sum = pre[n] - pre[i];
        double add = min(1LL*x*k,1LL*(m-i));
        double res = (sum+add)/x;
        ans = max(ans,res);
    }
    cout << fixed << setprecision(10) << ans << '\n';

    return 0;
}

