#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int ang; cin >> ang;
        int y = 180/__gcd(180,ang);
        bool found = false;
        for (int x = 1; x <= 180000; x++) {
            int n = y*x;
            if (1 <= x && x*ang/__gcd(180,ang) <= n - 2) {
                cout << n << '\n';
                //cout << x*ang/__gcd(180,ang) << '\n';
                found = true;
                break;
            }
        }
        if (!found) {
            cout << -1 << '\n';
        }
    }

    return 0;
}

