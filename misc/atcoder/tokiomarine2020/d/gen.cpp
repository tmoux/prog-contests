#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    random_device device;
    mt19937 gen(device());
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int v = gen() % n + 1;
        int L = gen() % n + 1;
        cout << v << ' ' << L << '\n';
    }
    cout << 100000 << '\n';
    for (int i = 0; i < n; i++) {
        int v = gen() % n + 1;
        int L = gen() % n + 1;
        cout << v << ' ' << L << '\n';
    }
}
