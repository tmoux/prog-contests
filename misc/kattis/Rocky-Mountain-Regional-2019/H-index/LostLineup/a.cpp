#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    int lo = 0, hi = n+1;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] >= mid) cnt++;
        }
        if (cnt >= mid) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }
    cout << lo << '\n';
    return 0;
    for (int i = n; i >= 1; i--) {
        auto it = lower_bound(a.begin(),a.end(),i);
        int num = distance(it,a.end());
        if (num >= i) {
            cout << i << '\n';
            return 0;
        }
    }
}

