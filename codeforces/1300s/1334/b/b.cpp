#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, x; cin >> n >> x;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(),a.end(),greater<int>());
        int i = 0;
        ll sum = 0;
        for (; i < n; i++) {
            sum += a[i];
            if (sum < 1LL*x*(i+1)) break;
        }
        cout << i << '\n';
    }
}
