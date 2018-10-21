#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int smalls[] = {0,0,6,28,96,252,550,1056,1848};

ll calc(int k) {
	ll sq = k*k-1;
	ll ans = (k-4)*(k-4)*(sq-8);
	ans += 4*(sq-2);
	ans += 8*(sq-3);
	ans += 4*(sq-4);
	ans += 4*(k-4)*(sq-4);
	ans += 4*(k-4)*(sq-6);
	return ans/2;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		if (i <= 4) {
			cout << smalls[i] << '\n';
		}
		else {
			cout << calc(i) << '\n';
		}
	}
	
	
	return 0;
}

