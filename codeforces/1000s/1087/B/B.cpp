#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    int minans = 999999999;
    for (int i = 1; i*i <= n; i++) {
        if (n % i == 0) {
            int p = i;
            int q = n/i;
            if (p < k) {
                //cout << p << ' ' << q << '\n';
                int x = q*k+p;
                //cout << x << '\n';
                minans = min(minans,x);
            }

            swap(p,q);
            if (p < k) {
                //cout << p << ' ' << q << '\n';
                int x = q*k+p;
                //cout << x << '\n';
                minans = min(minans,x);
            }
        }
    }
    cout << minans << '\n';

    return 0;
}

