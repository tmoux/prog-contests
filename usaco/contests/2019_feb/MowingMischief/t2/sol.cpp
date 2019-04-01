#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) begin(x),end(x)
#define x first
#define y second

struct Node {
	int s, e, m;
	//covers s,e;
	int maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		maxi = 0;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void add(int i, int x) {
		if (s == e) {
			maxi = max(maxi,x);
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		maxi = max(l->maxi,r->maxi);
	}

	int getmaxi(int st, int en) {
		if (st <= s && e <= en) {
			return maxi;
		}
		int ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	
};

const int maxn = 2e5+5;
int N, T;
vector<pair<int,int>> LIS[maxn];
pair<int,int> pts[maxn];
int lis[maxn];
ll dp[2][maxn];

struct Point
{
	int x, y, id;
};

struct Interval
{
	int se, en;
	vector<Point> ps; //list of points in this interval
} is[4*maxn];

void build(int i, int se, int en) {
    is[i].se = se;
    is[i].en = en;
	is[i].ps.clear();
    if (se == en) return;
    int m = (se+en)>>1;
    build(i*2,se,m);
    build(i*2+1,m+1,en);
}

void addInterval(int i, int l, int r, Point p) {
    if (l <= is[i].se && is[i].en <= r) {
        is[i].ps.push_back(p);
        return;
    }
    if (is[i].se == is[i].en) return;
    int mid = (is[i].se+is[i].en)/2;
    if (mid >= l) addInterval(i*2,l,r,p);
    if (mid < r) addInterval(i*2+1,l,r,p);
}

vector<Point> curr;
vector<Point> alls;

void solve(int i, int l, int r) {
	//DFS through segment tree
	int t0 = curr.size();
	for (auto p: is[i].ps) {
		curr.push_back(p);
	}
	
	if (is[i].se == is[i].en) {
		dp[1][is[i].se] = 1e14;
		int j = is[i].se;
		for (auto p: curr) {
			dp[1][j] = min(dp[1][j],dp[0][p.id] + 1LL*(pts[j].x-p.x)*(pts[j].y-p.y));
		}
		//printf("(%d, %d): %d\n",pts[j].x,pts[j].y,dp[1][j]);
	}
	else {
		int m = (is[i].se+is[i].en)/2;
		pair<ll,int> opt = {1e14,-1};
		for (auto p: curr) {
			opt = min(opt,{dp[0][p.id]+abs(1LL*(pts[m].x-p.x)*(pts[m].y-p.y)),p.id});
		}
		int b = opt.second;
		cout << b << '\n';
		solve(i*2,l,r);
		solve(i*2+1,l,r);
	}
	
	while (curr.size() > t0) curr.pop_back();
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("mowing.in","r",stdin);
	//freopen("mowing.out","w",stdout);
	cin >> N >> T;
	for (int i = 1; i <= N; i++) {
		int x, y; cin >> x >> y;
		pts[i] = {x,y};
	}
	pts[N+1] = {T,T};
	sort(pts,pts+N+2);
	Node *seg = new Node(0,T);
	LIS[0].push_back(pts[0]);
	for (int i = 1; i <= N+1; i++) {
		int mxcnt = seg->getmaxi(0,pts[i].y); //since all x,y are distinct
		//cout << i << ": " << pts[i].first << ' ' << pts[i].second << ": " << mxcnt << '\n';
		lis[i] = mxcnt + 1;
		LIS[mxcnt+1].push_back(pts[i]);
		seg->add(pts[i].y,mxcnt+1);
	}
	int maxLIS = lis[N+1];
	//establish the intervals [l,r] where each point is relevant
	//for calculating lis[x+1]
	for (int i = 0; i < maxLIS; i++) {
		for (int j = 0; j < LIS[i].size(); j++) {
			dp[0][j] = dp[1][j];
		}
		//printf("%d, size = %d\n",i,LIS[i].size());
		vector<pair<int,int>>& nxt = LIS[i+1];
		build(1,0,nxt.size()-1);
		int l = 0, r = 0;
		alls.clear();
		for (int j = 0; j < LIS[i].size(); j++) {
			pair<int,int> p = LIS[i][j];
			alls.push_back({p.x,p.y,j});
			while (nxt[l].x < p.x && l+1 < nxt.size()) l++;
			r = l;
			while (r + 1 < nxt.size() && nxt[r+1].y > p.y) r++;
			//printf("%d: (%d, %d): [%d, %d]\n",i,p.x,p.y,l,r);
			if (p.x < nxt[l].x && p.y < nxt[r].y) {
				addInterval(1,l,r,{p.x,p.y,j});
			}
		}
		/*
		cout << i << '\n';
		for (int j = 1; j <= 10; j++) {
			printf("[%d, %d]:\n",is[j].se,is[j].en);
			for (auto p: is[j].ps) {
				printf("(%d, %d)\n",p.x,p.y);
			}
			cout << '\n';
		}
		*/
		for (int j = 0; j < LIS[i+1].size(); j++) {
			pts[j] = LIS[i+1][j];
		}
		solve(1,0,LIS[i].size()-1);
	}
	ll ans = dp[1][0];
	cout << ans << '\n';

    return 0;
}