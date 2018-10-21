#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n; cin >> n;
	if (1 < n && n <= 3) {
		cout << "NO SOLUTION\n";
		return 0;
	}
	for (int i = 2; i <= n; i+=2) {
		cout << i << ' ';
	}
	for (int i = 1; i <= n; i+=2) {
		cout << i << ' ';
	}
	
	
	return 0;
}

