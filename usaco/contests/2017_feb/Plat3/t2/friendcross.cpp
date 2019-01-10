#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define f first
#define s second
#define MAXN 100005

typedef long long ll;
typedef pair<int, int> pi;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> PBDS;

int N, K;
pi idx[MAXN];
PBDS s[MAXN];

int query(int x, int y) {
	//++x;
	int sum = 0;
	while (x > 0) {
		sum += s[x].order_of_key(y + 1);
		x -= x & -x;
	}
	return sum;
}

void update(int x, int y) {
	//++x;
	while (x <= N) {
		s[x].insert(y);
		x += x & -x;
	}
}

int main() {
	freopen("friendcross.in", "r", stdin);
	freopen("friendcross.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		int num; cin >> num;
		idx[num].f = i + 1;
	}
	for (int i = 0; i < N; ++i) {
		int num; cin >> num;
		idx[num].s = i + 1;
	}

	ll ans = 0;
	for (int i = N; i > 0; --i) {
		int j = i + K + 1; if (j > N) continue;
		update(idx[j].f, idx[j].s);
		ans += query(N, idx[i].s);
		ans += query(idx[i].f, N);
		ans -= 2 * query(idx[i].f, idx[i].s);
	}

	cout << ans << "\n";

	return 0;
}