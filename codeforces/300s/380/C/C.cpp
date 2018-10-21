#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int lg(int x) { return 32 - __builtin_clz(x) - 1;}

const int maxn = 1e6+6, maxk = 21;
int n, m, pfx[maxn], mn[maxk][maxn];
map<int,vector<int>> vs;
int range_min(int l, int r) {
	int k = lg(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}

int query(int l, int r) {

}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    string s; cin >> s;
    n = s.size();
    for (int i = 0; i < n; i++) {
    	pfx[i+1] = (s[i] == '(' ? 1 : -1);
    	pfx[i+1] += pfx[i];
    	vs[pfx[i+1]].push_back(i+1);
    }
    //rmq
    for (int i = 1; i <= n; i++)
    	mn[0][i] = pfx[i];
    for (int k = 1; k < maxk; k++) {
    	for (int i = 1; i <= n; i++) {
    		int j = i + (1 << (k-1));
    		if (j + (1 << (k-1)) - 1 <= n) {
    			mn[k][i] = min(mn[k-1][i],mn[k-1][j]);
    		}
    	}
    }

    //answer queries
    cin >> m;
    while (m--) {
    	int l, r; cin >> l >> r;
    	int ans = query(l,r);
    }



    return 0;
}