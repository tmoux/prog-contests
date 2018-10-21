#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <set>
using namespace std;

const int maxn = 1e5+5, sq = (int)(sqrt(maxn)+1);
int N, val[maxn], val1[maxn], ans[maxn], bucket[maxn], block;
int pfx[sq][maxn];
vector<int> adj[maxn];

int nGreater(int l, int r, int x) {
	//# in range [l,r] greater than x
	if (bucket[l] == bucket[r]) {
		int res = 0;
		for (int i = l; i <= r; i++) {
			if (val[i] > x) res++;
		}
		return res;
	}
	int res = 0;
	while (l != 0 && bucket[l] == bucket[l-1]) {
		if (val[l] > x) res++;
		l++;
	}
	while (bucket[l] != bucket[r]) {
		res += pfx[bucket[l]][x+1];
		l += block;
	}
	for (int i = l; i <= r; i++) {
		if (val[i] > x) res++;
	}
	return res;
}

int pre = 0, preorder[maxn], postorder[maxn];
void dfs(int i, int par) {
	preorder[i] = pre++;
	val[preorder[i]] = val1[i];
	for (int j: adj[i]) {
		if (j == par) continue;
		dfs(j,i);
	}
	postorder[i] = pre - 1;
}

int main() 
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("promote.in","r",stdin); freopen("promote.out","w",stdout);
	scanf("%d",&N);
	pair<int,int> vs[maxn];
	for (int i = 0; i < N; i++) {
		int ai; scanf("%d",&ai);
		vs[i] = {ai,i};
	}
	sort(vs,vs+N);
	for (int i = 0; i < N; i++) {
		val1[vs[i].second] = i;
	}
	for (int i = 1; i < N; i++) {
		int p; scanf("%d",&p); p--;
		adj[p].push_back(i);
		adj[i].push_back(p);
	}

	//establish preorder #
	dfs(0,0);
	//sqrt decomp
	block = (int)(sqrt(N));
	for (int i = 0; i < N; i++) {
		bucket[i] = i/block;
	}
	vector<int> curr;
	for (int i = 0; i < N; i++) {
		curr.push_back(val[i]);
		if (i == N - 1 || bucket[i] != bucket[i+1]) {
			sort(curr.begin(),curr.end());
			for (int j = N - 1; j >= 0; j--) {
				pfx[bucket[i]][j] = pfx[bucket[i]][j+1];
				if (curr.empty()) continue;
				if (j == curr.back()) {
					pfx[bucket[i]][j]++;
					curr.pop_back();
				}
			}
			curr.clear();
		}
	}
	
	for (int i = 0; i < N; i++) {
		int ans = nGreater(preorder[i],postorder[i],val1[i]);
		printf("%d\n",ans);
	}


	return 0;
}