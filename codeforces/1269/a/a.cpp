#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool isPrime(int x) {
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int b = 4; ; b += 2) {
        int a = n+b;
        if (!isPrime(a)) {
            cout << a << ' ' << b << endl;
            return 0;
        }
    }
}

