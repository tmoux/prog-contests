#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k;
    cin >> n;
    k = n/2;
    random_device device;
    mt19937 gen(device());
    cout << n << ' ' << k << '\n';
    for (int i = 0; i < k*2; i++) {
        cout << i+1 << ' ';
    }
    cout << '\n';
    for (int i = 2; i <= n; i++) {
        int p = (gen() % (i-1)) + 1;
        cout << i << ' ' << p << '\n';
    }
}

