#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegDyn
{
	int s, e; //represents range [s,e]
	SegDyn *l, *r;
	int sum; //sum for this interval
	SegDyn(int _s, int _e) {
		s = _s;
		e = _e;
		l = NULL;
		r = NULL;
		sum = 0;
	}

	void prepareL() { if (l == NULL) l = new SegDyn(s,(s+e)/2); }
	void prepareR() { if (r == NULL) r = new SegDyn((s+e)/2+1,e); }

	void pull() {
		sum = 0;
		if (l) sum += l->sum;
		if (r) sum += r->sum;
	}

	void add(int idx, int del) { //a[idx] += del
		//cout << s << ' ' << e << '\n';
		if (s == e && s == idx) {
			//at the node, stop
			sum += del;
			return;
		}
		if (idx <= (s+e)/2) {
			prepareL();
			assert(l);
			l->add(idx,del);
		}
		else {
			prepareR();
			r->add(idx,del);
		}
		pull(); //updates current node based on the children
	}

	int getsum(int se, int en) {
        if (se > en) return 0;
		if (se <= s && e <= en) return sum;
		int res = 0;
		if (l && se <= (s+e)/2) res += l->getsum(se,en);
		if (r && en > (s+e)/2) res += r->getsum(se,en);
		return res;	
	}
};

const int maxn = 1e5+5;
SegDyn* bit[maxn];
int N, T;

void add(int i, int y, int del) {
    if (i > N) return;
    for (; i <= N; i += i & (-i))
        bit[i]->add(y,del);
}

int sum(int i, int y1, int y2) {
    if (i <= 0) return 0;
    assert(1 <= i && i <= N);
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i]->getsum(y1,y2);
    }
    return r;
}

int getRangeSum(int x1, int x2, int y1, int y2) {
    return sum(x2,y1,y2) - sum(x1-1,y1,y2); 
}

struct Q
{
	bool isQuery;
	bool isStart;
	int x, y1, y2, t;
	Q(bool a, bool b, int _x, int _y1, int _y2, int _t) :
		isQuery(a), isStart(b), x(_x), y1(_y1), y2(_y2), t(_t) {}
};

int main()
{
    freopen("mowing.in","r",stdin); freopen("mowing.out","w",stdout);
    cin >> N >> T;
    vector<Q> qs;
    int xp, yp; cin >> xp >> yp;
    int maxy = 0;
    for (int i = 2; i <= N; i++) {
    	int x, y; cin >> x >> y;
        maxy = max(maxy,y);
    	if (xp == x) { //vertical
    		qs.push_back(Q(1,0,x,min(yp,y),max(yp,y),i));
    	}
    	else {
    		//horizontal
            assert(yp == y);
            if (min(xp,x)+1 <= max(x,xp)-1) {
                qs.push_back(Q(0,1,min(xp,x)+1,yp,y,i));
                qs.push_back(Q(0,0,max(x,xp)-1,yp,y,i));
            }
    	}
    	xp = x; yp = y;
    }

    for (int i = 0; i <= N; i++) bit[i] = new SegDyn(0,maxy+1);

    sort(qs.begin(),qs.end(),[](const Q& a, const Q& b) {
    	if (a.x != b.x) return a.x < b.x;
        int t1 = a.isStart ? 1 : a.isQuery ? 0 : -1;
        int t2 = b.isStart ? 1 : b.isQuery ? 0 : -1;
        return t1 > t2;
    });

    ll res = 0;
    for (Q q: qs) {
        if (q.isStart) {
            //add the point to the line
            add(q.t,q.y1,1);       
            //printf("Added point (%d, %d)\n",q.t,q.y1);
        }
        else if (q.isQuery) {
            int r = getRangeSum(1,N,q.y1+1,q.y2-1) - getRangeSum(max(1,q.t-T),min(N,q.t+T),q.y1+1,q.y2-1); 
            //printf("Queried [%d,%d], from %d to %d: %d\n",q.y1,q.y2,max(1,q.t-T),min(N,q.t+T),r);
            res += r;
        }
        else {
            assert(!q.isStart && !q.isQuery);
            add(q.t,q.y1,-1);        
            //printf("Removed point (%d, %d)\n",q.t,q.y1);
        }
        /*
    	cout << q.isQuery << ' ' << q.isStart << '\n';
    	printf("%d %d %d %d\n\n",q.x,q.y1,q.y2,q.t);
        */
    }
    cout << res << '\n';
    return 0;
}
