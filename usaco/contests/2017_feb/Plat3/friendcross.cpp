#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
//2nd dimension will be a dynamic segtree, cuz why not
//never mind, this thing costs insane amounts of memory
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
		if (se <= s && e <= en) return sum;
		int res = 0;
		if (l && se <= (s+e)/2) res += l->getsum(se,en);
		if (r && en > (s+e)/2) res += r->getsum(se,en);
		return res;	
	}
};
*/

/*
struct SegNode
{
	int s, e; //represents range [s,e]
	SegNode *l, *r;
	ordered_set<int> root; //ordered set
	SegNode(int _s, int _e, int n) { //y-coordinates from [0,n]
		s = _s;
		e = _e;
		if (s == e) {
			//make a new segtree, x = s = e
			l = NULL;
			r = NULL;
			return;
		}
		l = new SegNode(s,(s+e)/2,n); 
		r = new SegNode((s+e)/2+1,e,n);
	}

	void add(int x, int y, int del) {
		root.insert(y);
		if (s == e) return;
		if (x <= (s+e)/2) {
			l->add(x,y,del);
		}
		else {
			r->add(x,y,del);
		}
	}

	int getsum(int x0, int x1, int y0, int y1) {
		if (x0 <= s && e <= x1) return root.order_of_key(y1);
		int res = 0;
		if (x0 <= (s+e)/2) res += l->getsum(x0,x1,y0,y1);
		if (x1 > (s+e)/2) res += r->getsum(x0,x1,y0,y1);
		return res;
	}
};
*/

struct Fen {
    int* bit;
    int s;
    vector<int> cols;
    map<int,int> colToIdx;
    void init(int _s) {
        s = _s;
        bit = new int[s+1];
        for (int i = 0; i <= s; i++) bit[i] = 0;
    }
    void init(const vector<int>& _c) {
        s = _c.size();
        cols = _c;
        bit = new int[s+1];
        for (int i = 0; i <= s; i++) bit[i] = 0;

        //indexing
        colToIdx[0] = 0;
        for (int i = 0; i < cols.size(); i++) {
            colToIdx[cols[i]] = i+1;
        }
    }

    void add(int i, int x) {
        for (; i <= s; i += i & (-i))
            bit[i] = (bit[i]+x) % M;
    }

    int sum(int i) {
        if (i == 0) return 0;
        int r = 0;
        for (; i; i -= i & (-i)) {
            r = (r+bit[i]) % M;
        }
        return r;
    }

    int idxForQuery(int i) {
        auto it = upper_bound(all(cols),i);
        if (it == cols.begin()) return 0;
        --it;
        return colToIdx[*it];
    }

    void insertValue(int col, int x) {
        int i = colToIdx[col];
        add(i,x);
    }

    int getValue(int col) {
        int i = idxForQuery(col);
        return sum(i);
    }
};

const int maxn = 1e5+5;
int N, K;
int a[maxn], pos[maxn];
int s[4*maxn], e[4*maxn];
vector<int> covers[4*maxn];
Fen seg[4*maxn];
void build(int i, int l, int r) {
	s[i] = l;
	e[i] = r;
	if (l == r) {
		return;
	}
	int m = (l+r)/2;
	build(i*2,l,m);
	build(i*2+1,m+1,r);
}

void add(int i, int x, int y) {
	seg[i].insert(y);
	if (s[i] == e[i]) return;
	if (x <= (s[i]+e[i])/2) add(i*2,x,y);
	else add(i*2+1,x,y);
}

int getsum(int i, int x0, int x1, int y1) {
	if (x0 <= s[i] && e[i] <= x1) return seg[i].order_of_key(y1);
	int res = 0;
	if (x0 <= (s[i]+e[i])/2) res += getsum(i*2,x0,x1,y1);
	if (x1 > (s[i]+e[i])/2) res += getsum(i*2+1,x0,x1,y1);
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("friendcross.in","r",stdin); freopen("friendcross.out","w",stdout);
    cin >> N >> K;
    build(1,0,N);
    for (int i = 1; i <= N; i++) {
    	cin >> a[i];
    }
    for (int i = 1; i <= N; i++) {
    	int ai; cin >> ai;
    	pos[ai] = i;
    }
    ll ans = 0;
    for (int i = N; i >= 1; i--) {
    	int q = getsum(1,0,N,pos[a[i]]) - getsum(1,max(1,a[i]-K),min(N,a[i]+K),pos[a[i]]);
    	ans += q;
    	//cout << a[i] << ": " << q << '\n';
    	add(1,a[i],pos[a[i]]);
    }
    cout << ans << '\n';

    return 0;
}
