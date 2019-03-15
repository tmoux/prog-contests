#include <bits/stdc++.h>
using namespace std;

int main()
{
	int ans = 0;
	for (int i = 0; i < 5; i++) {
		char c; cin >> c;
		ans += (c == 'P');
	}
	cout << ans << '\n';
}
