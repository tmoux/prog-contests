#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int minSeen = a[n-1];
        int ans = 0;
        for (int i = n-1; i >= 0; i--) {
            if (minSeen < a[i]) {
                ans++;
            }
            minSeen = min(minSeen,a[i]);
        }
        cout << ans << '\n';
    }

}

