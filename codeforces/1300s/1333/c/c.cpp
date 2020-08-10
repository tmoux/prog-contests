#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];
ll pre[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = a[i] + pre[i-1];
    }
    multiset<ll> ms;
    ms.insert(0);
    int pt = 1;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        while (pt <= n && !ms.count(pre[pt])) {
            ms.insert(pre[pt]);
            pt++;
        }
        //cout << i << ": " << pt << endl;
        ans += pt-i;
        auto it = ms.find(pre[i-1]);
        ms.erase(it);
    }
    cout << ans << '\n';
}
