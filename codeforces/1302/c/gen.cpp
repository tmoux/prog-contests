#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    int t, n; cin >> t >> n;
    cout << t << '\n';
    while (t--) {
        cout << n << ' ' << n << '\n';
        for (int i = 0; i < n; i++) {
            int tt = gen() % 2;
            cout << tt+1 << ' ';
            if (tt == 0) {
                int x = (gen()%n)+1;
                int y = gen() % 1000000000;
                cout << x << ' ' << y << '\n';
            }
            else {
                int l = (gen()%n)+1;
                int r = (gen()%n)+1;
                if (l > r) swap(l,r);
                cout << l << ' ' << r << '\n';
            }
        }
    }
}

