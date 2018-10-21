#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;



int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n, k, ti, ans = 0; cin >> n >> k;
	while (n--) {
		cin >> ti;
		ans += (ti % k == 0);
	}
	cout << ans << '\n';	
	
	return 0;
}