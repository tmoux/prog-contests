#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    n *= 2;
    vector<int> a(n);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    sort(a.begin(),a.end());
    ll hs = 0;
    for (int i = 0; i < n/2; i++) {
        hs += a[i];
    }
    if (sum-hs != hs) {
        for (int i = 0; i < n; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
    }
    else {
        cout << -1 << '\n';
    }
}

