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
    ll A, B, x, y, z;
    cin >> A >> B >> x >> y >> z;
    ll a1 = 0, a2 = 0;
    a1 += 2*x;
    a1 += y;
    a2 += y;
    a2 += 3*z;
    ll ans = 0;
    if (a1 > A) ans += a1-A;
    if (a2 > B) ans += a2-B;
    cout << ans << '\n';


    return 0;
}
	

