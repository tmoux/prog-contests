#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    cout << n << '\n';
    for (int i = 0; i < n - 1; i++) {
        int r = (rand() % i)+1;    
        cout << i << ' ' << r << '\n';
    }
    for (int i = 0; i < m; i++) {
        int v = (rand() % n) + 1;
        int d = (rand() % n);
        int x = rand() % 1000000000;
        cout << v << ' ' << d << ' ' << x << '\n';
    }

    return 0;
}

