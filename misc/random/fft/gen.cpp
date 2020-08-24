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
        for (int i = 0; i < n; i++) {
            cout << (gen() % 10);
        }
        cout << ' ';
        for (int i = 0; i < n; i++) {
            cout << (gen() % 10);
        }
        cout << '\n';
    }
}
