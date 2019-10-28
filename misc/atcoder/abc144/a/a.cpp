#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b; cin >> a >> b;
    if (a <= 9 && b <= 9) {
        cout << (a*b) << '\n';
    }
    else {
        cout << -1 << '\n';
    }
}

