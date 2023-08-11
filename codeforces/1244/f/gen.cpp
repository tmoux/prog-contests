#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    srand(time(NULL));
    int n; cin >> n;
    cout << n << ' ' << 10 << '\n';
    for (int i = 0; i < n; i++) {
        cout << (rand() % 2 == 0 ? 'W' : 'B');
    }
    cout << '\n';
}

