#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;



int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int T; cin >> T;
	for (int i = 0; i < T; i++) {
		int n; cin >> n;
		ll ans = 0;
		ll fv = 5;
		while (n/fv != 0) {
			ans += n/fv;
			fv *= 5;
		}
		cout  << ans << '\n';
	}
	
	return 0;
}