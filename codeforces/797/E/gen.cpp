#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int r = (rand() % n) + 1;
        cout << r << ' ';
    }
    cout << '\n'; 
    cout << q << '\n';
    for (int i = 0; i < q; i++) {
        int p = (rand() % n) + 1;
        int k = (rand() % n) + 1;
        cout << p << ' ' << k << '\n';
    }

    return 0;
}

