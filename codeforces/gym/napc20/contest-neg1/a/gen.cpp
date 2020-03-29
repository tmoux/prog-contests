#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int k = 3;
    cout << n << ' ' << k << '\n';
    random_device device;
    mt19937 gen(device());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2*k+1; j++) {
            int r = (gen() % 2000000000) - 1000000000;
            cout << r << ' ';
        }
        cout << '\n';
    }
}
