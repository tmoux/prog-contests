#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    int n, q, b; cin >> n >> q >> b;
    int mb = 1000000000;
    cout << n << ' ' << q << ' ' << b << '\n';
    for (int i = 0; i < n; i++) {
        int r = gen() % mb + 1;
        cout << r << ' '; 
    }
    cout << '\n';
    while (q--) {
        int t = rand() % 2;
        t = 0;
        if (t == 0) {
            cout << "Q ";
            int l = rand() % n + 1;
            int r = rand() % n + 1;
            if (l > r) swap(l,r);
            cout << l << ' ' << r << '\n';
        }
        else {
            cout << "U ";
            int x = rand() % n + 1;
            int v = rand() % mb + 1;
            cout << x << ' ' << v << '\n';
        }
    }
}

