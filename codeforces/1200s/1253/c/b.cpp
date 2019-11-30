#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m, a[maxn];

int ans[maxn];
ll mod_add[maxn];
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a,a+n);
    ll sum = 0;
    for (int k = 1; k <= n; k++) {
        mod_add[(k-1)%m] += a[k-1];
        sum += mod_add[(k-1)%m];
        cout << sum << ' ';
    }
    cout << '\n';
}
