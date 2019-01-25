#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
#define x first
#define y second

int h, w;
vector<vector<char>> grid;
vector<vector<int>> degree;
const int maxn = 1e5+5, maxk = 18;
int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};

inline bool valid(pii p) {
	return (0 <= p.x && p.x < h && 0 <= p.y && p.y < w);
}

int turn(pii a, pii c) {
	if (a.x == c.x || a.y == c.y) return 0;
	return 1;
}

struct edge
{
	int to, weight;
};
vector<edge> adj[maxn];
map<pii,int> mp;
map<int,pii> inv;
int p = 0;
int par[maxk][maxn];
int pfx[maxn];
int depth[maxn];

int dfs(pii curr, pii from) { //returns idx of node
	int idx = ++p;
	mp[curr] = idx;
	inv[idx] = curr;
	for (int k = 0; k < 4; k++) {
		pii next = {curr.x+dx[k],curr.y+dy[k]};
		if (!valid(next) || next == from) continue;
		if (grid[next.x][next.y] != '#') continue;
		int wt = turn(from,next);
		int j = dfs(next,curr);
		adj[idx].push_back({j,wt});
		par[0][j] = idx;
		
	}
	return idx;
}

void dfs2(int i, int p) {
	pfx[i] += pfx[p];
	depth[i] = depth[p] + 1;
	for (edge e: adj[i]) {
		if (e.to == p) continue;
		pfx[e.to] += e.weight;
		dfs2(e.to,i);
	}
}

int getClosest(int a, int lc) {
	assert(depth[a] > depth[lc]);
	for (int k = maxk-1; k >= 0; k--) {
		int aa = par[k][a];
		if (aa != 0 && depth[aa] > depth[lc]) a = aa;
	}
	return a;
}

int main()
{
	//freopen("in","r",stdin);
	scanf("%d %d\n",&h,&w);
	//initialize grid
	for (int i = 0; i < h; i++) {
		grid.push_back(vector<char>(w));
		degree.push_back(vector<int>(w));
		for (int j = 0; j < w; j++) {
			cin >> grid[i][j];
		}
	}
	bool found = false;
	for (int i = 0; i < h && !found; i++) {
		for (int j = 0; j < w && !found; j++) {
			if (grid[i][j] != '#') continue; 
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (!valid({nx,ny})) continue;
				if (grid[nx][ny] == '#') degree[i][j]++;
			}
			if (degree[i][j] == 1) {
				//is leaf, start dfs
				pii root = {i,j};
				dfs(root,root);
				found = true;
				break;
			}
		}
	}

	for (int k = 1; k < maxk; k++) {
		for (int i = 1; i <= p; i++) {
			par[k][i] = par[k-1][par[k-1][i]];
			//printf("%d'th ancestor of %d: %d\n",1<<k,i,par[k][i]);
		}
	}
	dfs2(1,1);
	//answer queries
	int q; cin >> q;
	while (q--) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d\n",&x1,&y1,&x2,&y2);
		--x1; --y1; --x2; --y2;
		int a = mp[{x1,y1}];
		int b = mp[{x2,y2}];
		//handle special case, because timus is probably evil
		if (a == b) {
			//no turns necessary
			cout << 0 << '\n';
			continue;
		}
		if (depth[a] > depth[b]) swap(a,b);
		int a_copy = a, b_copy = b;
		for (int k = maxk-1; k >= 0; k--) {
			int bb = par[k][b];
			if (bb != 0 && depth[bb] >= depth[a]) b = bb;
		}
		if (a == b) {
			//a is direct ancestor of b
			int close = getClosest(b_copy,a_copy);
			int ans = pfx[b_copy] - pfx[close];
			cout << ans << '\n';
		}
		else {
			for (int k = maxk-1; k >= 0; k--) {
				int aa = par[k][a];
				int bb = par[k][b];
				if (aa != bb) {
					a = aa;
					b = bb;
				}
			}
			int ans = pfx[a_copy] - pfx[a] + pfx[b_copy] - pfx[b];
			pii t1 = inv[a];
			pii t2 = inv[b];
			if (turn(t1,t2)) ++ans;
			cout << ans << '\n';
		}
	}
	return 0;
}