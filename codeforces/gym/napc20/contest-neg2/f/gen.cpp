#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    int n, q; cin >> n >> q;
    cout << n << ' ' << q << '\n';
    for (int i = 1; i <= n; i++) {
        int ran = gen() % n + 1;
        cout << ran << ' ';
    }
    cout << '\n';
    for (int i = 2; i <= n; i++) {
        int r = gen() % (i-1) + 1;
        cout << r << ' ' << i << '\n';
    }
    while (q--) {
        int a = gen() % n + 1;
        int b = gen() % n + 1;
        cout << a << ' ' << b << '\n';
    }
}
