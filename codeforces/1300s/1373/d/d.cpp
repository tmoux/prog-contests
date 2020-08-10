#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n), b(n);
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            b[i] = a[i];
            if (i % 2 == 0) {
                sum += a[i];
                b[i] *= -1;
            }
        }
        vector<ll> pre(n,0);
        for (int i = 0; i < n; i++) {
            pre[i] = b[i];
            if (i > 0) pre[i] += pre[i-1];
        }
        ll maxsum = 0;
        ll mn0 = b[0], mn1 = 0;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                maxsum = max(maxsum,pre[i]-mn0);
                mn0 = min(mn0,pre[i]);
            }
            else {
                maxsum = max(maxsum,pre[i]-mn1);
                mn1 = min(mn1,pre[i]);
            }
        }
        cout << (sum+maxsum) << '\n';
    }
}
