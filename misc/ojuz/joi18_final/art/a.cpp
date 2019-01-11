#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5+5;
int N;
pair<ll,ll> a[maxn];

ll f(int l, int r) {
	if (l > r) return 0;
	if (l == r) {
		return a[l].second;
	}	
	int m = (l+r)/2;
	//get max of arrays that go thru mid
	ll lmax = 0, lcurr = 0;
	for (int i = m; i >= l; i--) {
		lcurr += a[i].second;
		lmax = max(lmax,lcurr-(a[m].first-a[i].first));
	}
	ll rmax = 0, rcurr = 0;
	for (int i = m + 1; i <= r; i++) {
		rcurr += a[i].second;
		rmax = max(rmax,rcurr-(a[i].first-a[m].first));
	}
	return max(lmax+rmax,max(f(l,m),f(m+1,r)));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
    	cin >> a[i].first >> a[i].second;
    }
    sort(a,a+N);
    ll ans = f(0,N-1);
    cout << ans << '\n';

    return 0;
}