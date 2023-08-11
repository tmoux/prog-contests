#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll b; cin >> b;
    int r = 0;
    for (ll i = 1; i*i <= b; i++) {
        if (b % i == 0) {
            r += i*i == b ? 1 : 2;
        }
    }
    cout << r << '\n';

    return 0;
}

