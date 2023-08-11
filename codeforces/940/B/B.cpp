#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
ll n, k, A, B;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> k >> A >> B;
	ll cost = 0;
	if (k == 1) {
		cout << A*(n-1) << '\n';
		return 0;
	}
	while (n != 1) {
		//cout << n << '\n';
		if (n < k) {
			cost += A*(n-1);
			break;
		}
		else if (n == k) {
			cost += min(B,A*(n-1));
			break;
		}
		else if (n % k == 0) {
			ll nn = n/k;
			cost += min(B,(n-nn)*A);
			n = nn;
		}
		else {
			ll nn = n/k*k;
			cost += (n-nn)*A;
			n = nn;
		}
	}
	cout << cost << '\n';
	return 0;
}

