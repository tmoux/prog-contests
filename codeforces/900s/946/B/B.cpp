#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

typedef long long ll;

void calc(long long& a, long long& b) {
	//cout << a << ' '  << b << '\n';
	if (a == 0 || b == 0) {
		return;
	}
	if (a == 2*b) {
		a = 0;
		return;
	}
	if (b == 2*a) {
		b = 0;
		return;
	}
	if (a >= 2*b) {
		ll numdivide = (ll)ceil((a-2*b)/(double)(2*b));
		//cout << numdivide << '\n';
		a -= numdivide*(2*b);
		calc(a,b);
		return;
	}
	if (b >= 2*a) {
		ll numdivide = (ll)ceil((b-2*a)/(double)(2*a));
		b -= numdivide*(2*a);
		calc(a,b);
	}
	return;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	long long a, b;
	cin >> a >> b;
	calc(a,b);
	cout << a << ' ' << b << '\n';
	
	
	return 0;
}

