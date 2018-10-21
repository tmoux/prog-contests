#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+100, sq = (int)(sqrt(maxn)), M = 1e9+9;
int n, q, A[maxn], fib[maxn], block, sum[maxn];
vector<pair<int,int>> queries;
int pfx[maxn];

void update() {
	pfx[2] = (pfx[2] + pfx[1]) % M;
	for (int i = 3; i <= n; i++) {
		pfx[i] = ((pfx[i] + pfx[i-1]) % M + pfx[i-2]) % M;
	}
	for (int i = 1; i <= n; i++) {
		A[i] = (A[i] + pfx[i]) % M;
	}

	for (int i = 1; i <= n; i++) {
		sum[i] = (sum[i-1] + A[i]) % M;
	}
	memset(pfx,0,sizeof(pfx));
	queries.clear();
}

int main()
{
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    scanf("%d %d",&n,&q);
    for (int i = 1; i <= n; i++) {
    	scanf("%d",A+i);
    }
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i <= n + 5; i++) fib[i] = (fib[i-1] + fib[i-2]) % M;
    //sqrt decomposition
    block = (int)sqrt(n);
	update();
	
	while (q--) {
		int t, l, r; scanf("%d %d %d",&t,&l,&r);
		if (t == 1) {
			pfx[l] = (pfx[l] + 1) % M;
			pfx[r+1] = (pfx[r+1] + M - fib[r-l+2]) % M;
			pfx[r+2] = (pfx[r+2] + M - fib[r-l+1]) % M;
			queries.push_back({l,r});
			if (queries.size() == block) update();
		}
		else {
			int res = (sum[r] + M - sum[l-1]) % M;
			for (pair<int,int>& p: queries) {
				if (p.first > r || p.second < l) continue;
				int ll = max(p.first,l);
				int rr = min(p.second,r);
				int s = ll - p.first + 1;
				int e = (rr-ll) + s;
				int add = (fib[e+2] - fib[s+1] + M) % M;
				res = (res + add) % M;
			}
			printf("%d\n",res);
		}
	}

    return 0;
}