#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool prime(int x) {
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x; cin >> x;
    while (!prime(x)) x++;
    cout << x << '\n';
}

