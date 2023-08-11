#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
typedef long long ll;

ll n;
const ll maxn = 200005;
vector<ll> bs, ps, rs;
pair<ll,char> A[maxn];
const ll INF = -2009009009;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//input
	//freopen("input.in","r",stdin);
	cin >> n;
	ll ans = 0;
	ll lastr = INF, lastb = INF, lastp = INF;
	ll maxb = 0, maxr = 0, maxp = 0;
	for (ll i = 0; i < n; i++) {
		ll ai; char c;
		cin >> ai >> c;
		if (c == 'B') {
			if (lastb != INF) {
				ans += ai - lastb;
				maxb = max(maxb,ai-lastb);
			}
			lastb = ai;
		}
		else if (c == 'R') {
			if (lastr != INF) {
				ans += ai - lastr;
				maxr = max(maxr,ai-lastr);
			}
			lastr = ai;
		}
		else {
			if (lastb != INF) {
				ans += ai-lastb;
				maxb = max(maxb,ai-lastb);
			}
			lastb = ai;
			if (lastr != INF) {
				ans += ai-lastr;
				maxr = max(maxr,ai-lastr);
			}
			lastr = ai;
			if (lastp != INF) {
				ll tmp = (ai-lastp)*3-maxr-maxb;
				if (tmp < (ai-lastp)*2) {
					ans -= (ai-lastp)*2-tmp;
				}			
			}
			lastp = ai;
			maxb = 0;
			maxr = 0;
		}
	}
	cout << ans << '\n';
	
	
	
	
	
	
	
	return 0;
}