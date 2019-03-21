#include <bits/stdc++.h>
using namespace std;
using ll = long long;
/*
 * Problem is essentially a series of 3-d queries, i.e,
 * for a set of points in R^3 (x,y,x+y), find those with
 * z-coordinate above z, y coordinate above y, and x-coord
 * above x.
 * One dimension, z, can be removed by answering the queries
 * offline and simulating the queries with a line sweep and 
 * answering the queries using 2-d segtree.
 * I used a BIT for x-coordinate and dynamic segtree for 
 * y-axis. However, due to memory constraints, I had to 
 * coordinate-compress both the x and y coordinates
 * to fit under the 1G limit. (Note that after sorting
 * the points/queries by z-coordinate, coordinate-compression
 * does not affect the 2-d queries.)
*/
struct SegDyn
{
	int s, e, m; //represents range [s,e]
	SegDyn *l, *r;
	int sum; //sum for this interval
	SegDyn(int _s, int _e) {
		s = _s;
		e = _e;
		m = (s+e)/2;
		l = NULL;
		r = NULL;
		sum = 0;
	}

	void prepareL() { if (l == NULL) l = new SegDyn(s,m); }
	void prepareR() { if (r == NULL) r = new SegDyn(m+1,e); }

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
		if (idx <= m) {
			prepareL();
			//assert(l);
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
		if (l && se <= m) res += l->getsum(se,en);
		if (r && en > m) res += r->getsum(se,en);
		return res;	
	}
};

const int maxn = 1e5+5, MAX = 1e9+5;
int N, Q;
SegDyn* xs[2*maxn];
void add(int x, int y) {
    for (; x <= N+Q; x += x & (-x)) {
        xs[x]->add(y,1); 
    }
}
int sum(int x, int y1) {
    int r = 0;
    for (; x; x -= x & (-x)) {
        r += xs[x]->getsum(y1,N+Q);
    }
    return r;
}
struct Query
{
    int x, y, z; //z = x + y;
    bool isQuery;
    int id; //id # for queries
} queries[2*maxn];

int ans[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> Q;
    int pt = 0;
    for (int i = 0; i < N; i++) {
        int s, t; cin >> s >> t;
        queries[pt++] = {s,t,s+t,false,-1};
    }
    for (int i = 0; i < Q; i++) {
        int x, y, z; cin >> x >> y >> z;
        queries[pt++] = {x,y,z,true,i};
    }
    sort(queries,queries+N+Q,[](auto a, auto b) { 
            if (a.z != b.z) return a.z > b.z;
            return ((int)a.isQuery < (int)b.isQuery); });
    //coordinate compress x-coordinates
    vector<int> xcoords;
    vector<int> ycoords;
    for (int i = 0; i <= N+Q; i++) {
        xs[i] = new SegDyn(0,N+Q);
        if (i < N+Q) {
            xcoords.push_back(queries[i].x);
            ycoords.push_back(queries[i].y);
        }
    }
    sort(xcoords.begin(),xcoords.end());
    sort(ycoords.begin(),ycoords.end());
    xcoords.erase(unique(xcoords.begin(),xcoords.end()),xcoords.end());
    ycoords.erase(unique(ycoords.begin(),ycoords.end()),ycoords.end());
    map<int,int> mp;
    pt = 1;
    for (int x: xcoords) mp[x] = pt++;
    map<int,int> mp2;
    pt = 1;
    for (int y: ycoords) mp2[y] = pt++;
    //try to compress y-coordinates too (for memory reasons)
    for (int i = 0; i < N+Q; i++) {
        queries[i].x = mp[queries[i].x];            
        queries[i].y = mp2[queries[i].y];
        //cout << queries[i].x << ' ' << queries[i].y << ' ' << queries[i].z << ' ' << queries[i].isQuery << '\n';
    }
    //now process queries
    for (int i = 0; i < N + Q; i++) {
        auto q = queries[i];
        if (!q.isQuery) {
            add(q.x,q.y);
        }
        else {
            int res = sum(N+Q,q.y) - sum(q.x-1,q.y);
            ans[q.id] = res;
        }
    }
    //output queries
    for (int i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }
}

