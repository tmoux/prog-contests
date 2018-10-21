#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

int n, m;
int a[1001];

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int ci; cin >> ci;
		a[ci]++;
	}
	int ans = 99999;
	for (int i = 1; i <= n; i++) {
		ans = min(ans,a[i]);
	}
	cout << ans << '\n';
	
	
	return 0;
}