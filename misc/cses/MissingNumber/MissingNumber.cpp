#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool seen[500005];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n; cin >> n;
	for (int i = 0; i < n-1; i++) {
		int ai; cin >> ai;
		seen[ai] = true;
	}
	for (int i = 1; i <= n; i++) {
		if (!seen[i]) {
			cout << i << '\n';
			break;
		}
	}
	
	return 0;
}

