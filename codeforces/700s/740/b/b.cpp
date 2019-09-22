#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n, m;
int a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i-1];
    }
    int ans = 0;
    while (m--) {
        int l, r; cin >> l >> r;
        int sum = a[r] - a[l-1];
        if (sum > 0) ans += sum;
    }
    cout << ans << '\n';
}

