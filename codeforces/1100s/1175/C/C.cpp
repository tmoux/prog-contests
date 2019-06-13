#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        k++;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        if (n == 1) {
            cout << a[0] << '\n';
            continue;
        }
        else {
            int minans = 2e9+9;
            int res = -1;
            for (int i = 0; i + k <= n; i++) {
                int x = (a[i+k-1] + a[i])/2;
                int r = max(a[i+k-1]-x,x-a[i]);
                //cout << a[i] << ": " << x << ' ' << r << '\n';
                if (r < minans) {
                    minans = r;
                    res = x;
                }
            }
            assert(res != -1);
            cout << res << '\n';
        }
    }
}

