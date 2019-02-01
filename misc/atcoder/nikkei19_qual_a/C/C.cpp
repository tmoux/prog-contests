#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
int a[maxn], b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    ll ans = 0;
    vector<pair<int,int>> as;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        ans -= b[i];
        as.push_back({a[i],b[i]});
    }
    sort(as.begin(),as.end(),[](auto x, auto y) { return x.first + x.second > y.first + y.second; });
    for (int i = 0; i < n; i += 2) {
        ans += as[i].first + as[i].second;
    }
    cout << ans << '\n';

    return 0;
}

