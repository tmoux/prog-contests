#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(int n, int m) {
    int perRow = (m+1)/2;
    if (n == 1) {
        return ((m+1)/3);
    }
    else if (n == 2) {
        return perRow;
    }
    else {
        ll ans = 1LL*((n+1)/3)*perRow;
        if (n % 3 == 1) {
            ans += (m+1)/3;
            return ans;
        }
        else {
            return ans;
        }
    }
    assert(false);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    ll ans = max(solve(n,m),solve(m,n));
    cout << ans << '\n';
    
}

