#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    int n; cin >> n;
    cout << n << '\n';
    while (n--) {
        int a = gen() % 1000000000+1;
        int b = gen() % 1000000000+1;
        cout << a << ' ' << b << '\n';
    }
}
