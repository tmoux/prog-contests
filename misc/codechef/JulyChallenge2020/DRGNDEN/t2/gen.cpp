#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    random_device device;
    mt19937 gen(device());
    cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; i++) {
        //cout << (gen() % 5 + 1) << ' ';
        cout << abs(i-n/2) + 3 << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cout << (gen() % n + 1) << ' ';
    }
    cout << '\n';
    while (q--) {
        int t = gen() % 2 + 1;
        int b = gen() % n + 1;
        int c = gen() % n + 1;
        cout << t << ' ' << b << ' ' << c << '\n';
    }
}
