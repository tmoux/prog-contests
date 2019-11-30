#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ceil(int a, int b) {
    return (a+b-1)/b;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--)  {
        int r, b, k; cin >> r >> b >> k;
        if (r < b) swap(r,b);
        if (r == b) {
            cout << "OBEY\n";
        }
        else {
            int gc = __gcd(r,b);
            //starting point
            int mx = ceil(r-gc,b);
            if (mx < k) {
                cout << "OBEY\n";
            }
            else {
                cout << "REBEL\n";
            }
        }
    }
}

