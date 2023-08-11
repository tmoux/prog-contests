#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    srand(time(NULL));
    cout << n << ' ' << q << '\n';
    for (int i = 2; i <= n; i++) {
        int p = rand() % (i-1) + 1;
        cout << p << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= n; i++) {
        int r = rand() % 10000 - 5000;
        cout << r << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= n; i++) {
        int r = rand() % 10000 - 5000;
        cout << r << ' ';
    }
    cout << '\n';
    while (q--) {
        int t = rand() % 2 + 1;
        int v = rand() % n + 1;
        cout << t << ' ' << v;
        if (t == 1) {
            int x = rand() % 5000 + 1;
            cout << ' ' << x << '\n';
        }
        else {
            cout << '\n';
        }
    }
}

