#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5+5;
int n;
ll pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pre[i];
        pre[i] += pre[i-1];
    }
    if (pre[n] % 3 != 0) {
        cout << 0 << '\n';
        return 0;
    }
    
    int d2 = 0;
    ll p1 = pre[n]/3, p2 = pre[n]/3*2;
    for (int i = 1; i <= n-1; i++) {
        if (pre[i] == p2) d2++;
    }

    ll ans = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (pre[i] == p2) d2--;
        if (pre[i] == p1) {
            ans += d2;
        }
    }
    cout << ans << '\n';
    
    return 0;
}
	

