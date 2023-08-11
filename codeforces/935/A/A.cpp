#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n; cin >> n;
	int numWays = 0;
	for (int i = 1; i < n; i++) {
		if ((n-i) % i == 0) {
			numWays++;
		}
	}
	cout << numWays << '\n';
	
	
	return 0;
}

