#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int maxn = 1e5+5, sq = (int)(sqrt(maxn))+1;
int n, q, A[maxn];

int query(int l, int r, int X) {
	int res = 0;
	for (int i = l; i <= r; i++) {
        if (A[i] <= X) res++;
    }
	return res;
}
 
int main()
{
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> A[i];

	while (q--) {
		char c; cin >> c;
		if (c == 'M') {
			int i, X; cin >> i >> X;
			A[i] = X;
		}
		else {
			int p, q, X; cin >> p >> q >> X;
			int ans = query(p,q,X);
			cout << ans << '\n';
			//cout << p << ' ' << q << '\n';
		}
	}
 
 
    return 0;
}
