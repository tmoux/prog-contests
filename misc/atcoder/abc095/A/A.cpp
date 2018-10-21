#include <iostream>
using namespace std;

int main()
{
	string s; cin >> s;
	int ans = 700;
	for (char c: s) {
		if (c == 'o') ans += 100;
	}
	cout << ans << '\n';
	return 0;
}