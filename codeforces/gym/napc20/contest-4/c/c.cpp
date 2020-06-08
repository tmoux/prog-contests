#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t; cin >> t;
	while (t--) {
		int n, d; cin >> n >> d;
		vector<ll> v(n);
		for (int i = 0; i < n; i++) cin >> v[i];
		for (int i = 1; i <= n+1; i++) {
			v.push_back(-1LL*i*d);
		}
		sort(v.begin(),v.end());
		ll ans = 0;
		for (int i = 0; i < v.size(); i++) {
			v[i] -= 1LL*i*d;
		}
		priority_queue<ll> pq;
		for (auto i: v) {
			pq.push(i);
			if (pq.top() > i) {
				ans += pq.top()-i;
				pq.pop();
				pq.push(i);
			}
		}
		cout << ans << '\n';
	}
}