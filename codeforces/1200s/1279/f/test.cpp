#include <bits/stdc++.h>
#define pll pair<ll,ll>
#define FOR(i,a,b) for (int i = a; i <= b; i++)
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 5;
int n, k, l, sm[MAXN];
char s[MAXN];
pll dp[MAXN];
 
ll solve(char a) {
	FOR(i, 1, n) sm[i] = sm[i-1] + (s[i] == a);
	int lo = 0, hi = l; ll ans = 0;
	while (lo <= hi) {
		int mi = (lo+hi) / 2;
		FOR(i, 1, l) dp[i] = max(dp[i-1], {sm[i]-mi, -1});
		FOR(i, l+1, n) {
			dp[i] = max(dp[i-1], {dp[i-l].first+sm[i]-sm[i-l]-mi, dp[i-l].second-1});
            cout << i << ": " << dp[i].second << endl;
        }
		if (-dp[n].second <= k) {
			hi = mi-1, ans = dp[n].first;
        }
		else
			lo = mi+1;
	}
	return sm[n] - k * lo - ans;
}
 
int main() {
	scanf("%d %d %d", &n, &k, &l);
	scanf("%s", s+1);
	if ((ll)k * (ll)l >= n)
		return !printf("0\n");
	FOR(i, 1, n) s[i] = 'a' <= s[i] ? 'a' : 'b';
	printf("%lld\n", min(solve('a'), solve('b')));
	return 0;
}
