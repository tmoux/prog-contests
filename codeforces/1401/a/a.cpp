#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        int nn = max(n,k);
        if (nn % 2 != k % 2) nn++;
        cout << (nn-n) << '\n';
    }
}
