#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
struct Point
{
    int x, y;

    bool operator<(const Point& rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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

map<Point,ll> lc, rc;
ll yl[maxn], yr[maxn];

void cnt(const vector<Point>& v, int i) {
    map<int,int> maxx;
    Node *root = new Node(1,maxn);
    for (Point p: v) {
        if (maxx.count(p.x)) root->add(maxx[p.x],-1);
        maxx[p.x] = max(maxx[p.x],p.y);
        root->add(maxx[p.x],1);
        ll c = root->getsum(p.y,maxn);
        (i==0?lc[p]:rc[p]) = c;
        (i==0?yl[p.y]:yr[p.y]) += c;
        //printf("(%d,%d): %d\n",p.x,p.y,root->getsum(p.y,maxn));
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    vector<Point> v;
    map<int,int> ycnt;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v.push_back({x,y});
        ycnt[y]++;
    }
    sort(v.begin(),v.end(),[](auto a, auto b) {
            return a.y < b.y;
            });
    map<int,int> mpY;
    int pt = 1;
    for (Point& p: v) {
        if (mpY.count(p.y)) {
            p.y = mpY[p.y];
        }
        else {
            p.y = mpY[p.y] = pt++;
        }
    }
    //now y are compressed
    sort(v.begin(),v.end(),[](auto a, auto b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
            });
    cnt(v,0);
    //cout << ans << '\n';
    sort(v.begin(),v.end(),[](auto a, auto b) {
            if (a.x != b.x) return a.x > b.x;
            return a.y < b.y;
            });
    cnt(v,1);
    ll ans = 0;
    for (Point& p: v) {
        //printf("(%d, %d): %d, %d: %d\n",p.x,p.y,(int)lc[p],(int)rc[p],(int)lc[p]*rc[p]);
        ans += 1LL*lc[p]*rc[p];
    }
    //subtract out overcounting
    map<int,vector<Point>> mp;
    sort(v.begin(),v.end());
    for (auto p: v) {
        mp[p.y].push_back(p);
    }
    for (auto& pp: mp) {
        auto vec = pp.second;
        for (int i = 0; i < vec.size()-1; i++) {
            ans -= lc[vec[i]]*rc[vec[i+1]];
        }
    }

    cout << ans << '\n';
}

