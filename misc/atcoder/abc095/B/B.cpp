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
	int n, x; cin >> n >> x;
	int minCost = 99999;
	for (int i = 0; i < n; i++) {
		int mi; cin >> mi;
		minCost = min(minCost,mi);
		x -= mi;
	}
	int ans = n + (x/minCost);
	cout << ans << '\n';
	
	
	return 0;
}