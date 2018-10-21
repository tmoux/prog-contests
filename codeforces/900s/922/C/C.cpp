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
	//freopen("input.in","r",stdin);
	ll n, k; cin >> n >> k;
	bool ans = true;
	if (n <= k && k != 1 && n != 1) {
		ans = false;
	}
	else {
		for (ll i = 1; i <= k; i++) {
			if (n % i != i-1) {
				ans = false;
				break;
			}
		}
	}
	if (ans) {
		cout << "Yes\n";
	}
	else {
		cout << "No\n";
	}

	
	return 0;
}