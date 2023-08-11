#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int mask = 1; mask < (1<<n); mask++) {
        int total = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                total += a[i];
            }
            else total -= a[i];
        }
        total %= 360;
        if (total == 0) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";

    return 0;
}

