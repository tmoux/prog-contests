#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int k; cin >> k;
    int M = 1000000;
    while ((k+M) % 1999 != 0) M--;
    assert((k+M) % 1999 == 0);
    int y = (k+M)/1999;
    int x = M - y;
    //cout << M << ' ' << x << '\n';
    cout << 1999 << '\n';
    for (int i = 0; i < 1997; i++) {
        cout << 0 << ' ';
    }
    cout << -x << ' ';
    cout << M << '\n';
    //cout << ((M-x)*1999) << ' ' << (M+k) << '\n';
}

