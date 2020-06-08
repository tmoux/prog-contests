#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << 1 << '\n';
    int c = 50000;
    cout << 2 << ' ' << c << '\n';
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < c; j++) {
            cout << 0;
        }
        cout << '\n';
    }
    for (int i = 0; i < c-1; i++) {
        cout << 'R';
    }
    cout << 'D';
    cout << '\n';
    cout << 'U';
    for (int i = 0; i < c-1; i++) {
        cout << 'L';
    }
    cout << '\n';
}
