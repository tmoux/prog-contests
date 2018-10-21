#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

typedef long long ll;

void calc(ll& a, ll& b) {
	//cout << a << ' ' << b << '\n';
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
		a %= 2*b;
		
		calc(a,b);
	}
	else if (b >= 2*a) {
		b %= 2*a;
		calc(a,b);
	}
	
	return;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	ll a, b;
	cin >> a >> b;
	calc(a,b);
	cout << a << ' ' << b << '\n';
	
	
	return 0;
}

