#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; i++) {
        cout << (rand() % n) + 1 << ' ';
    }
    cout << '\n';
    for (int i = 0; i < m; i++) {
        int t = rand() % 2;
        cout << t << ' ';
        if (t == 0) {
            cout << (rand() % n) + 1 << ' ' << (rand() % n) + 1 << '\n';
        }
        else {
            cout << (rand() % n) + 1 << '\n';
        }
    }

    return 0;
}

