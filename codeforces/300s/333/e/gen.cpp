#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n << '\n';
    random_device device;
    mt19937 gen(device());
    while (n--) {
        int x = gen() % 20000 - 10000;
        int y = gen() % 20000 - 10000;
        cout << x << ' ' << y << '\n';
    }
}

