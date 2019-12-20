#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    int n; cin >> n;
    int k = gen() % 1000000000 + 1;
    cout << n << ' ' << k << '\n';
    for (int i = 0; i < n; i++) {
        int r = gen() % 1000000000 + 1;
        cout << r << ' ';
    }
    cout << '\n';
}

