#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            cout << "(";
        }
        else {
            cout << "R";
        }
    }
    cout << '\n';
}

