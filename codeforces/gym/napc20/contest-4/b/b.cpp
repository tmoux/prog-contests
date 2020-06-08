#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll cnt[1<<20];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t; cin >> t;
	while (t--) {
		memset(cnt,0,sizeof cnt);
		int n; cin >> n;
		vector<int> v(n);
		for (int i = 0; i < n; i++) {
			cin >> v[i];
			cnt[v[i]]++;
		}
		for (int i = 0; i < 20; i++) {
			for (int mask = 0; mask < (1<<20); mask++) {
				if (mask & (1<<i)) {
					cnt[mask] += cnt[mask^(1<<i)];
				}
			}
		}
		ll ans = 0;
		for (int i = 0; i < n; i++) ans += cnt[v[i]];
		cout << ans << '\n';
	}
}