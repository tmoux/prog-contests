#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define all(x) begin(x),end(x)

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, l, r, x; cin >> n >> l >> r >> x;
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    int ans = 0;
    for (int mask = 1; mask < (1<<n); mask++) {
        vector<int> use;
        int total = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1<<i)) {
                use.push_back(c[i]);
                total += c[i];
            }
        }
        sort(all(use));
        if (total >= l && total <= r && use.back() - use.front() >= x) ans++;        
    }
    cout << ans << '\n';

    return 0;
}

