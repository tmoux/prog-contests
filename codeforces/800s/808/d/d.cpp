#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
ll a[maxn];
ll pre[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = a[i] + pre[i-1];
    }
    if (pre[n] % 2 == 1) {
        cout << "NO\n";
        return 0;
    }
    ll target = pre[n]/2;
    multiset<ll> ms;
    for (int i = 1; i <= n; i++) {
        ms.insert(a[i]);
    }
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        if (ms.count(target-sum)) {
            cout << "YES\n";
            return 0;
        }
        sum += a[i];
        auto it = ms.find(a[i]);
        ms.erase(it);
        if (sum > target) break;
    }
    ms.clear();
    for (int i = 1; i <= n; i++) {
        ms.insert(a[i]);
    }
    sum = 0;
    for (int i = n; i >= 1; i--) {
        if (ms.count(target-sum)) {
            cout << "YES\n";
            return 0;
        }
        sum += a[i];
        auto it = ms.find(a[i]);
        ms.erase(it);
        if (sum > target) break;
    }
    cout << "NO\n";
}

