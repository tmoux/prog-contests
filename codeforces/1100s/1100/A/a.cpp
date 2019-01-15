#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, k, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0;
	for (int i = 1; i <= k; i++) {
		int r = 0;
		for (int j = 1; j <= n; j++) r += a[j];
		for (int j = i; j <= n; j += k) r -= a[j];
		r = abs(r);
		ans = max(ans,r);
	}
	cout << ans << '\n';

    return 0;
}