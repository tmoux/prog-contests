#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << 1 << '\n';
    int n; cin >> n;
    cout << n << '\n';
    while (n--) {
        int l = rand() % 1000 + 1;
        int r = rand() % 1000 + 1;
        if (l > r) swap(l,r);
        cout << l << ' ' << r << '\n';
    }
}

