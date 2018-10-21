#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int arr[500005];

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	ll ans = 0;
	for (int i = 1; i < n; i++) {
		if (arr[i] < arr[i-1]) {
			ans += (arr[i-1]-arr[i]);
			arr[i] = arr[i-1];
		}
	}
	cout << ans << '\n';
	
	
	return 0;
}

