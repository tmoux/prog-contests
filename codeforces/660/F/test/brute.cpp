#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
ll a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ll r = 0;
            for (int k = i; k <= j; k++) {
                r += a[k]*(k-i+1);        
            }
            ans = max(ans,r);
        }
    }
    cout << ans << '\n';


    return 0;
}

