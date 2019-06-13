#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        ll s = 0;
        while (n != 0) {
            if (n % k == 0) {
                n /= k;
                s++;
            }
            else {
                ll add = n - (k*(n/k));
                n -= add;
                s += add;
            }
        }
        cout << s << '\n';
    }
}

