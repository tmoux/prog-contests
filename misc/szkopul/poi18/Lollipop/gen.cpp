#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    random_device rd;
    mt19937 gen(rd());
    int n, m; cin >> n >> m;
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; i++) {
        int r = gen() % 2;
        if (r == 0) {
            cout << 'T';
        }
        else {
            cout << 'W';
        }
    }
    cout << '\n';
    for (int i = 0; i < m; i++) {
        int l = gen() % n + 1;
        cout << l << '\n';
    }
}

