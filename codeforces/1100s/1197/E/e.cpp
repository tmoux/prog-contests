#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, M = 1e9+7, INF = 2e9+9;
int n;

struct DP
{
    ll val, ways;
};

DP comb(DP l, DP r) {
    if (l.val < r.val) return l;
    else if (r.val < l.val) return r;
    return {l.val,(l.ways+r.ways)%M};
}

struct Node {
	int s, e, m;
	//covers s,e;
    DP dp;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
        dp = {INF,0};
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

	void add(int i, DP x) {
		if (s == e) {
            dp = comb(dp,x);
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
        dp = comb(l->dp,r->dp);    
	}

	DP getmini(int st, int en) {
		if (st <= s && e <= en) {
			return dp;
		}
        DP ret = {INF,0};
		if (st <= m) {
			ret = comb(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = comb(ret,r->getmini(st,en));
		}
		return ret;
	}	
};

struct Point
{
    int x, y, y_c, mul; //multiplicity

    bool operator<(const Point& rhs) const {
        return x != rhs.x ? x < rhs.x : y > rhs.y;
    }
};

map<Point,DP> ans;
set<Point> term; //set of terminal points

struct Seg {
	int s, e, m;
	//covers s,e;
	int sum;
	Seg *l, *r;
	
	Seg(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		if (s != e) {
			m = (s+e)/2;
			l = new Seg(s,m);
			r = new Seg(m+1,e);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}


	void add(int i, int x) {
		if (s == e) {
			sum += x;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		sum = l->sum + r->sum;
	}

	int getsum(int st, int en) {
		if (st <= s && e <= en) {
			return sum;
		}
		int ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    map<pair<int,int>,int> mp;
    set<int> ys, xs;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> y >> x;
        mp[make_pair(x,y)]++;
        ys.insert(y);
        xs.insert(x);
    }
    map<int,int> compress, compressX;
    int curr = 1;
    for (int y: ys) {
        compress[y] = curr++;
    }
    curr = 1;
    for (int x: xs) {
        compressX[x] = curr++;
    }
    xs.insert(INF);
    compressX[INF] = curr++;
    vector<Point> pts;
    for (auto p: mp) {
        pts.push_back({p.first.first,p.first.second,compress[p.first.second],p.second});
    }
    sort(pts.begin(),pts.end());
    Node *root = new Node(0,n);
    root->add(0,{0,1});
    int i = 0;
    ys.insert(0);
    compress[0] = 0;
    for (Point& p: pts) {
        auto it = ys.upper_bound(p.x);
        --it;
        DP dp = root->getmini(0,compress[*it]);
        //printf("querying [0,%d]\n",*it);
        //printf("%d %d\n",dp.val,dp.ways);
        dp.val += (p.x-p.y);        
        dp.ways = (dp.ways * p.mul) % M;
        root->add(p.y_c,dp);
        ans[p] = dp;
        //printf("(%d,%d): val = %d, ways = %d (x%d)\n",p.x,p.y,dp.val,dp.ways,p.mul);
        i++;
    }
    //count the terminal nodes
    sort(pts.begin(),pts.end(),[](auto a, auto b) {
            return a.x != b.x ? a.x > b.x : a.y_c < b.y_c;
            });
    Seg *seg = new Seg(1,n+1);
    for (Point& p: pts) {
        auto it = xs.lower_bound(p.y);
        //printf("(%d,%d): %d\n",p.x,p.y,seg->getsum(compressX[*it],n+1));
        if (seg->getsum(compressX[*it],n+1) == 0) {
            term.insert(p);
            //cout << "found " << p.x << ' ' << p.y << '\n';
        }
        seg->add(compressX[p.x],1);
    }
    DP res = {INF,0};
    for (Point& p: pts) {
        if (term.count(p)) {
            ans[p].val += p.y;
            assert(ans[p].val >= 1);
            //printf("testing (%d, %d): val = %d, ways = %d\n",p.x,p.y,ans[p].val,ans[p].ways);
            res = comb(res,ans[p]);
        }
    }
    //cout << res.val << '\n';
    cout << res.ways << '\n';
}
