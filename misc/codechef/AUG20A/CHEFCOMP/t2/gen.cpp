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
        cout << n << '\n';
        for (int i = 2; i <= n; i++) {
            int r = (gen() % (i-1)) + 1;
            cout << r << ' ' << i << '\n';
        }
        vector<int> p(n);
        iota(p.begin(),p.end(),1);
        shuffle(p.begin(),p.end(),gen);
        for (int i: p) cout << i << ' ';
        cout << '\n';
        for (int i = 1; i <= n; i++) {
            int r = (gen() % 1000000000) + 1;
            cout << r << ' ';
        }
        cout << '\n';
        for (int i = 1; i <= n; i++) {
            int r = (gen() % 1000000000) + 1;
            cout << r << ' ';
        }
        cout << '\n';
    }
}
