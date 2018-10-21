#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, sq = (int)(sqrt(maxn));
int n, m, A[maxn], freq[maxn];
vector<int> specials;
int pfx[2*sq][maxn];

int query(int l, int r) {
	int res = 0;
	for (int i = 0; i < specials.size(); i++) {
		if (pfx[i][r] - pfx[i][l-1] == specials[i]) res++;
	}
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
    	cin >> A[i];
    	if (A[i] <= n) {
    		freq[A[i]]++;
    		if (A[i] == freq[A[i]]) {
    			specials.push_back(A[i]);
    		}
    	}
    }

    for (int i = 0; i < specials.size(); i++) {
    	for (int j = 1; j <= n; j++) {
    		pfx[i][j] = pfx[i][j-1];
    		if (A[j] == specials[i]) pfx[i][j]++;
    	}
    }

    while (m--) {
    	int l, r; cin >> l >> r;
    	int ans = query(l, r);
    	cout << ans << '\n';
    }


    return 0;
}