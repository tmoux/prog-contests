#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    int n, q; cin >> n >> q;
    cout << n << ' ' << q << '\n';
    while (q--) {
        int t = (gen() % 3) + 1;
        int x = gen() % n + 1;
        int y = gen() % n + 1;
        cout << t << ' ' << x << ' ' << y << '\n';
    }
}

