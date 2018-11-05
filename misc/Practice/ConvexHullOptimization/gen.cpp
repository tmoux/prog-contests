#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; i++) {
        int m = (rand() % 1000) - 500;
        int b = (rand() % 1000) - 500;
        cout << m << ' ' << b << '\n';
    }
    for (int i = 0; i < q; i++) {
        int x = (rand() % 1000) - 500;
        cout << x << '\n';
    }

    return 0;
}

