#include <bits/stdc++.h>
using namespace std;
using ll = long long;

random_device device;
mt19937 gen(device());

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; i++) {
        int ai = (gen() % 2000000000) - 1000000000;
        cout << ai << ' ';
    }
    cout << '\n';
    for (int i = 2; i <= n; i++) {
        int p = (gen() % (i-1)) + 1;
        cout << p << ' ' << i << '\n';
    }
    for (int i = 0; i < q; i++) {
        int t = gen() % 2 + 1;    
        //int t = 1;
        int r = gen() % n + 1;
        int k = gen() % n + 1;
        cout << t << ' ' << r << ' ' << k << '\n';
    }
}

