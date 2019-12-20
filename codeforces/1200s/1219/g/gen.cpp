#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    random_device device;
    mt19937 gen(device());
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int r = gen() % 1000000000;
            cout << r << ' ';
        }
        cout << '\n';
    }
}
