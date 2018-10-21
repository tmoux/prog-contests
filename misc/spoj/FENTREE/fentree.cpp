#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const ll maxn = 1000005;
ll BIT[maxn], arr[maxn], n;
//arrays are 1-based
void update(ll x, ll delta) {
	for (; x <= n; x += x&-x) {
		BIT[x] += delta;
	}
}
ll pfxsum(ll x) {
	//sums from 1 to x
	ll sum = 0;
	for (; x > 0; x -= x&-x) {
		sum += BIT[x];
	}
	return sum;
}

ll query(ll l, ll r) {
	return pfxsum(r)-pfxsum(l-1);
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n;
	for (ll i = 1; i <= n; i++) {
		cin >> arr[i];
		update(i,arr[i]);
	}
	ll q; cin >> q;
	while (q--) {
		char u; ll a, b;
		cin >> u >> a >> b;
		switch (u) {
			case 'q':
				cout << query(a,b) << '\n';
				break;
			case 'u':
				update(a,b);
				break;
		}
	}	
	return 0;
}