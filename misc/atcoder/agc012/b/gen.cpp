#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    cout << "100000 99999\n";
    for (int i = 0; i < 99999; i++) {
        cout << 1 << ' ' << i+2 << '\n';
    }
    cout << 100000 << '\n';
    for (int i = 0; i < 100000; i++) {
        int v = gen() % 100000 + 1;
        int d = gen() % 11;
        int c = gen() % 100000 + 1;
        cout << v << ' ' << d << ' ' << c << '\n';
    }
}

