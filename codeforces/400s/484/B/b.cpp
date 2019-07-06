#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a,a+n);
    int ans = 0;
    for (int i = n-2; i >= 0; i--) {
        if (a[i]-1 < ans) break;
        if (a[i] == a[i+1]) continue;
        for (int j = 2*a[i]; j <= 1000000+a[i]; j += a[i]) {
            auto it = lower_bound(a,a+n,j);
            --it;
            if (*it > j-a[i]) {
                ans = max(ans,*it-(j-a[i]));
            }
        }
    }
    cout << ans << '\n';
}

