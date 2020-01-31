#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    int n; cin >> n;
    int k = gen() % 1000000;
    cout << n << ' ' << n << ' ' << k << '\n';
    for (int i = 0; i < n; i++) {
        cout << (gen() % 1000000) << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        int l = gen() % n + 1;
        int r = gen() % n + 1;
        if (l > r) swap(l,r);
        cout << l << ' ' << r << '\n';
    }
}

