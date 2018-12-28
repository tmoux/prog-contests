#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
const ll INF = 1LL<<62;
int n;
ll penalty[maxn], ans[maxn];
struct Edge
{
    int to; 
    ll weight;
};
vector<Edge> adj[maxn];
//convex hull optimization
typedef long double ld;
struct FN
{
    ll m, b; //in this case, function is a line
    FN(ll _m, ll _b) : m(_m), b(_b) {}
    ll eval(ll x) const {
        return m*x + b;
    }

    ld intersect(const FN& r) const { //returns x coordinate of intersection
        //assert(m != r.m);
        return (ld)(r.b-b)/(ld)(m-r.m);
    }

    friend bool comp(const FN& l1, const FN& l2, const FN& l) {
    	//order in deque: l1, l2, l
    	//true --> l2 is unnecessary
    	ld x1 = l1.intersect(l);
        ld x2 = l1.intersect(l2);
        return x1 <= x2;
    }
};

struct Hull: public deque<FN> //convex hull for maximum
{
    void addBack(const FN& l) {
        if (!this->empty() && this->back().m == l.m) {
            return;
        }
        while (this->size() >= 2 && 
            comp((*this)[this->size()-2],(*this)[this->size()-1],l)) {
            this->pop_back();    
        }
        this->push_back(l);
    }

    ll query(ll x) {
        if (this->empty()) return INF;
        while (this->size() >= 2 && this->front().eval(x) >= (*this)[1].eval(x)) {
            this->pop_front();
        }
        return this->front().eval(x);
        /*
        ll res = INF;
        for (FN fn: (*this)) {
            res = min(res,fn.eval(x));
        }
        return res;
        */
    }
};

//centroid decomp
bool blocked[maxn];
int sub_size[maxn];

int dfsSize(int i, int p) {
    sub_size[i] = 1;
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        sub_size[i] += dfsSize(e.to,i);
    }
    return sub_size[i];
}
int getCentroid(int i, int p, int compSize) {
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        if (sub_size[e.to] * 2 > compSize) return getCentroid(e.to,i,compSize);
    }
    return i;
}

struct Point {
    ll depth, mult, id;    
};

void dfs(int i, int p, ll dep, vector<Point>& pts) {
    pts.push_back({dep,penalty[i],i});
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        dfs(e.to,i,dep+e.weight,pts);
    }
}

void cht(int centroid) {
    vector<Point> pts;
    dfs(centroid,centroid,0,pts);
    sort(pts.begin(),pts.end(),[](auto& a, auto& b) {
            if (a.mult != b.mult) return a.mult > b.mult;
            return a.depth < b.depth;});
    Hull hull;
    for (Point p: pts) {
        FN fn(p.mult,p.depth);
        hull.addBack(fn);
    }
    reverse(pts.begin(),pts.end()); //now increasing in slope
    for (Point p: pts) {
        ans[p.id] = min(ans[p.id],hull.query(p.mult) + p.depth);
    }
}

void decomp(int i) {
    int compSize = dfsSize(i,i);
    int centroid = getCentroid(i,i,compSize);
    blocked[centroid] = true;
    cht(centroid);
    for (Edge e: adj[centroid]) {
        if (blocked[e.to]) continue;
        decomp(e.to);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> penalty[i];
        ans[i] = INF;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    decomp(1);
    ll res = 0;
    for (int i = 1; i <= n; i++) res += ans[i];
    cout << res << '\n';

    return 0;
}

