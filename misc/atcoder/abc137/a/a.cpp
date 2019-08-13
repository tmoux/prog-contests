#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
	int A, B; cin >> A >> B;
	int ans = A + B;
	ans = max(ans,A-B);
	ans = max(ans,A*B);
	cout << ans << '\n';
}