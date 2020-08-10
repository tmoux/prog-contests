#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    cout << n << ' ' << m << '\n';
    random_device device;
    mt19937 gen(device());
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << (gen()%2) << ' ';
        }
        cout << '\n';
    }
    while (m--) {
        int r = gen() % n + 1;
        int t = gen() % 4;
        cout << r << ' ' << t << '\n';
    }
}

