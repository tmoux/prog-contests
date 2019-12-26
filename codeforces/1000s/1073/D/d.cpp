#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
ll T;
int a[maxn];

int main() {
    cin >> n >> T;
    int mn = 2e9;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mn = min(mn,a[i]);
    }
    ll ans = 0;
    while (T >= mn) {
        int cnt = 0;
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            if (T >= a[i]) {
                cnt++;
                sum += a[i];
                T -= a[i];
                ans++;
            }
        }
        ll add = T/sum;
        ans += 1LL*cnt*add;
        T %= sum;
    }
    cout << ans << endl;
}
