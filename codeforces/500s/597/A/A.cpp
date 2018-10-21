#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll k, a, b; cin >> k >> a >> b;
    ll x1 = a/k*k;
    ll x2 = b/k*k;
    while (x1 < a) x1 += k;
    while (x2 > b) x2 -= k;
    if (x1 > x2) {
        cout << 0 << '\n';
        return 0;
    }
    ll ans = (ll)((x2-x1)/k+1);
    cout << ans << '\n';


    return 0;
}
	

