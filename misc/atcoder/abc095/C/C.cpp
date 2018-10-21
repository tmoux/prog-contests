#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

int A, B, C, X, Y, ans;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> A >> B >> C >> X >> Y;
	if (2 * C < A + B) {
		int minxy = min(X,Y);
		ans = 2 * C * minxy;
		//cout << ans << '\n';
		X -= minxy;
		Y -= minxy;
		//cout << X << ' '  << Y << '\n';
		ans += X * min(A,2*C);
		ans += Y * min(B,2*C);
		cout << ans << '\n';
	}
	else {
		ans = A * X + B * Y;
		cout << ans << '\n';
	}
	
	
	return 0;
}