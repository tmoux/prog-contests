#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << "200000 200000 1\n";
    for (int i = 0; i <= 200000; i++) {
        cout << i << ' ';
    }
    cout << '\n';
    cout << 200000 << '\n';
    for (int i = 0; i < 200000; i++) {
        int r = rand() % 500000;
        r *= 2;
        cout << r << ' ';
    }
    cout << '\n';
}
