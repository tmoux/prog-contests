#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int k; cin >> k;
    int d = 1;
    while (d <= k) d <<= 1;
    cout << 2 << ' ' << 3 << '\n';
    cout << (k|d) << ' ' << k << ' ' << 0 << '\n';
    cout << d << ' ' << (k|d) << ' ' << k << '\n';
}

