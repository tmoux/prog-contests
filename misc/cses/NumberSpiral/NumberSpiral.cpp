#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

ll getDiag(ll n) {
	return n*n-(n-1);
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int t; cin >> t;
	for (int i = 0; i < t; i++) {
		ll y, x;
		cin >> y >> x;
		ll diag = getDiag(max(y,x));
		int pari = max(y,x) % 2;
		if (y > x && pari == 1 || y < x && pari == 0) {
			diag -= abs(y-x);
		}
		else {
			diag += abs(x-y);
		}
		cout << diag << '\n';
	}
	
	return 0;
}

