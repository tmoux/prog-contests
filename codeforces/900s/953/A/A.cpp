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
	int l, r; cin >> l >> r;
	int ans = 0;
	for (int num2s = 0; num2s < 31; num2s++) {
		for (int num3s = 0; num3s < 20; num3s++) {
			ll testnum = (ll)(pow(2,num2s)*pow(3,num3s));
			if (testnum > r) break;
			if (l <= testnum && testnum <= r) {
				//cout << testnum << '\n';
				ans++;
			}
		}
	}
	cout << ans << '\n';
	
	return 0;
}