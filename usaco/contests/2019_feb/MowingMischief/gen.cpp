#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << 200000 << ' ' << 1000000 << '\n';
    for (int i = 0; i < 100000; i++) {
        cout << (i+1) << ' ' << (200000 - i) << '\n';
    }
    for (int i = 0; i < 100000; i++) {
        cout << (300000 + i ) << ' ' << (500000 - i) << '\n';
    }

    return 0;
}

