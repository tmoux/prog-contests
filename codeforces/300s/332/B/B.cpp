#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const ll maxn = 200005;
ll n, k;
ll pre[maxn], segsum[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (ll i = 1; i <= n; i++) {
        cin >> pre[i];
    }
    for (ll i = 1; i <= n; i++) {
        pre[i] += pre[i-1];
    }
    for (ll i = 1; i + k - 1 <= n; i++) {
        segsum[i] = pre[i+k-1] - pre[i-1];
    }

    ll ans = 0;
    ll maxfirst = n - k, maxsecond = n - k + 1;
    ll maxsecondAns;
    ll max2nd = segsum[n-k+1];
    for (ll i = n - k - k + 1; i >= 1; --i) {
        if (segsum[i+k] >= max2nd) {
            max2nd = segsum[i+k];
            maxsecond = i+k;
        }   
        if (segsum[i] + max2nd >= ans) {
            maxfirst = i;
            maxsecondAns = maxsecond;
            ans = segsum[i] + max2nd;
        }
       
    }
 
    cout << maxfirst << ' '<< maxsecondAns << '\n';
    if (n == 100000) {
        //cout << max2nd << ' ' << segsum[88779] << ' ' << segsum[89359] << '\n';
    }

    return 0;
}
	

