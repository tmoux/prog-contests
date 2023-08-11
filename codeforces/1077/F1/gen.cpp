#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k, x; cin >> n >> k >> x;
    cout << n << ' ' << k << ' ' << x << '\n';
    for (int i = 0; i < n; i++) {
        int r = (rand() % 1000000000) + 1;
        cout << r << ' ';
    }

    return 0;
}

