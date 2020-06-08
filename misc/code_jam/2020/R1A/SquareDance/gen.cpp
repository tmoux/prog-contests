#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int t = 100;
    for (int i = 0; i < t; i++) {
        cout << n << ' ' << n << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << rand() % 1000000 + 1 << ' ';
            }
            cout << '\n';
        }
    }
}
