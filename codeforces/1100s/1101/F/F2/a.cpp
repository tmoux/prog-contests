#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 405, maxm = 250005;
int n, m, a[maxn];
struct Truck
{
	int s, f, cost, refill;
} trucks[maxm];

bool poss(ll V, int i) {
	int R = trucks[i].refill;
	ll curr = V;
	for (int j = trucks[i].s; j < trucks[i].f; j++) {
		ll need = 1LL * (a[j+1] - a[j]) * trucks[i].cost;
		if (need > V) return false;
		if (need <= curr) {
			curr -= need;
		}
		else {
			if (R > 0) {
				curr = V - need;
				R--;
			}
			else {
				return false;
			}
		}
	}
	return true;
}

int main()
{
    scanf("%d %d",&n,&m);
    ll minPoss = 0;
	for (int i = 1; i <= n; i++) scanf("%d",a+i);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d",&trucks[i].s,&trucks[i].f,&trucks[i].cost,&trucks[i].refill);
	}
	for (int i = 0; i < m; i++) {
		for (int j = trucks[i].s; j < trucks[i].f; j++) {
			ll need = 1LL * (a[j+1] - a[j]) * trucks[i].cost;
			minPoss = max(minPoss,need);
		}
	}
	srand(time(0));
	random_shuffle(trucks,trucks+m);
	ll ans = minPoss;
	for (int i = 0; i < m; i++) {
		if (poss(ans,i)) continue;
		ll lo = ans-1, hi = 1e18+5;
		while (lo + 1 < hi) {
			ll m = (lo+hi)>>1;
			(poss(m,i)?hi:lo) = m;
		}
		ans = hi;
	}
	cout << ans << '\n';
    return 0;
}