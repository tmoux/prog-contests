#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	const int maxn = 5002;
	int plane[maxn];
	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> plane[i];
	}
	for (int i = 1; i <= n; i++) {
		//cout << i << ' ' << plane[plane[plane[i]]] << '\n';
		if (plane[plane[plane[i]]] == i) {
			cout << "YES\n";
			return 0;
		}
	}
	cout << "NO\n";	
	return 0;
}
