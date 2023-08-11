#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, k1, k2;
ll A[maxn], B[maxn], diffs[maxn];

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//input
	//freopen("input.in","r",stdin);
	cin >> n >> k1 >> k2;
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> B[i];
	}
	for (int i = 0; i < n; i++) {
		diffs[i] = abs(A[i]-B[i]);
	}
	
	//calculations
	int tot = k1+k2;
	multiset<ll,greater<ll>> s;
	for (int i = 0; i < n; i++) {
		s.insert(diffs[i]);
	}
	while (tot > 0) {
		ll f = *s.begin();
		s.erase(s.begin());
		s.insert(abs(f-1));
		tot--;
	}
	
	//output answer
	ll ans = 0;
	for (ll i: s) {
		ans += i*i;
	}
	cout << ans << '\n';
	
	return 0;
}