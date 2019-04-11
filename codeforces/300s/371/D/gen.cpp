#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    srand(time(NULL));
    int n, q; cin >> n >> q;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int r = rand() % 1000000000 + 1;
        cout << r << ' ';
    }
    cout << '\n';
    cout << q << '\n';
    while (q--) {
        int t = rand() % 2 + 1;
        cout << t << ' ';
        int i = rand() % n + 1;
        if (t == 1) {
            int x = rand() % 1000000000 + 1;
            cout << i << ' ' << x << '\n';
        }
        else {
            cout << i << '\n';
        }
    }
}

