#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    multiset<ll> ms;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        ms.insert(ai);
    }
    if (!(n&1)) ms.insert(0);
    ll ans = 0;
    while (ms.size() > 1) {
        ll a = *ms.begin();
        ms.erase(ms.begin());
        ll b = *ms.begin();
        ms.erase(ms.begin());
        ll c = *ms.begin();
        ms.erase(ms.begin());
        ms.insert(a+b+c);
        ans += a+b+c;
    }
    cout << ans << '\n';
}

