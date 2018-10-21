#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, INF = 2e9;
int n, q, A[maxn], bucket[maxn], block[maxn], sz;

int query(int l, int r) {
	int res = INF;
	if (bucket[l] == bucket[r]) {
		for (int i = l; i <= r; i++) 
			res = min(res,A[i]);
		return res;
	}
	while (l != 0 && bucket[l] == bucket[l-1]) {
		res = min(res,A[l]);
		l++;
	}
	while (bucket[l] != bucket[r]) {
		res = min(res,block[bucket[l]]);
		l += sz;
	}
	for (int i = l; i <= r; i++) {
		res = min(res,A[i]);
	}
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i];
    sz = (int)(sqrt(n));
	for (int i = 0; i < n; i++) {
		bucket[i] = (i)/sz;
		block[bucket[i]] = (block[bucket[i]] == 0 ? A[i] : min(A[i],block[bucket[i]]));
	}
	cin >> q;
	while (q--) {
		int l, r; cin >> l >> r;
		int ans = query(l,r);
		cout << ans << '\n';
	}


    return 0;
}