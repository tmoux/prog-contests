#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 300005;
int a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] != a[0]) {
            ans = max(ans,i);
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] != a[n-1]) {
            ans = max(ans,n-1-i);
            break;
        }
    }
    cout << ans << '\n';
}

