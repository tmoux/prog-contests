#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k, A = 5, B = 2089;
    cin >> n >> k;
    cout << n << ' ' << k << ' ' << A << ' ' << B << '\n';
    for (int i = 0; i < k; i++) {
        int r = (rand() % 10000000) + 1;
        cout << r << ' ';
    }
    cout << '\n';

    return 0;
}

