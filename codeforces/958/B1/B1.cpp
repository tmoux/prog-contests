#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 1001;
int arr[maxn];
int n;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n;
	for (int i = 0; i < n-1; i++) {
		int u, v; cin >> u >> v;
		arr[u]++;
		arr[v]++;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (arr[i] == 1) ans++;
	}
	cout << ans << '\n';	
	return 0;
}