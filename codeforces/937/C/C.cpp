#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
using namespace std;

typedef long long ll;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	ll k, d, t;
	cin >> k >> d >> t;
	double f = ceil(k*1.0/d)*d;
	long double fast = (k*1.0/(t*1.0));
	double slow = ((f-k)*1.0/(2*t));
	long double ans = floor(1.0/(fast+slow))*f;
	double amtLeft = 1.0-floor(1.0/(fast+slow))*(fast+slow);
	if (amtLeft <= fast) {
		ans += (amtLeft/fast*k);
	}
	else {
		ans += k;
		amtLeft-=(k*1.0/t);
		ans+= (amtLeft/slow)*(f-k);
	}
	cout << setprecision(10) << fixed << ans << '\n';

	
	
	return 0;
}

