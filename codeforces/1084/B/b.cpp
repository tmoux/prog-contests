#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; 
    ll s;
    cin >> n >> s;
    vector<int> a(n);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum < s) {
        cout << -1 << '\n';
        return 0;
    }
    sort(a.begin(),a.end());
    int lo = 0, hi = a[0]+1;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        ll t = 0;
        for (int i = 0; i < n; i++) {
            t += max(0,a[i]-mid);
        }
        //cout << mid << ": " << t << '\n';
        if (t >= s) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }
    cout << lo << '\n';
}

