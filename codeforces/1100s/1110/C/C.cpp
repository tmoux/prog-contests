#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int a; cin >> a;
        if ((a & (a+1)) == 0) {
            int maxFac = 1;
            for (int i = 2; i*i <= a; i++) {
                if (a % i == 0) {
                    maxFac = max(maxFac,max(i,a/i));
                }
            }
            cout << maxFac << '\n';
        }
        else {
            int res = 1;
            while (res <= a) res <<= 1;
            cout << res-1 << '\n';
        }
    }


    return 0;
}

