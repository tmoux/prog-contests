#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int r() { return rand() % 1000000000;}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; i++) {
        int x = r(), y = r(), t = r();
        cout << x << ' ' << y << ' ' << t << '\n';
    }
    for (int i = 0; i < m; i++) {
        int x = r(), y = r();
        cout << x << ' ' << y << '\n';
    }

    return 0;
}

