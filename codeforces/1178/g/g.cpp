#include <bits/stdc++.h>
using namespace std;
using ll = long long;
typedef long double ld;

const int maxn = 2e5+5;
int BLK;
int n, q;

int tin[maxn], tout[maxn];
ll a[maxn], b[maxn];
vector<int> adj[maxn];
int t = 0;

void DFS(int i) {
    tin[i] = t++;
    for (int j: adj[i]) {
        DFS(j);
    }
    tout[i] = t-1;
}

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
        //if (l2.m == l.m && l2.b <= l.b) return true;
        ld x1 = l1.intersect(l);
        ld x2 = l1.intersect(l2);
        return x1 <= x2;
    }
};

struct Hull: public deque<FN> //convex hull for maximum
{
    void add(const FN& l) {
        while (this->size() >= 2 && 
            comp((*this)[this->size()-2],(*this)[this->size()-1],l)) {
            this->pop_back();    
        }
        this->push_back(l);
    }

    ll query(ll x) {
        while (this->size() >= 2 && (*this)[1].eval(x) >= (*this)[0].eval(x)) {
            this->pop_front();
        }
        assert(!this->empty());
        return (*this)[0].eval(x);
    }
};

int bucket[maxn];
struct Block
{
    ll x = 0;    
    ll start;
    vector<int> indices, pos;
    vector<pair<ll,ll>> ps;
    Hull hull;
    void setup() {
        sort(indices.begin(),indices.end(),[](int x, int y) {
                return b[x] < b[y];
                });
        pos.resize(indices.size());
        for (int i = 0; i < indices.size(); i++) {
            pos[indices[i]-start] = i;
        }
        ps.resize(2*indices.size());
        refresh();
    }
    void refresh() {
        hull.clear();
        int pt = 0;
        for (int i: indices) {
            int p = pos[i-start];
            ps[p+indices.size()] = {b[i],a[i]*b[i]};
            ps[indices.size()-p-1] = {-b[i],-a[i]*b[i]};
        }
        /*
        sort(ps.begin(),ps.end(),[](auto& a, auto& b) {
                return a.first != b.first ? a.first < b.first :
                a.second < b.second;
                });
                */
        ll currSlope = -1e18;
        ll maxB = -1e18;
        for (int i = 0; i < ps.size(); i++) {
            if (ps[i].first != currSlope) {
                if (currSlope != -1e18) {
                    hull.add(FN(currSlope,maxB));
                }
                currSlope = ps[i].first;
                maxB = ps[i].second;
            }
            else {
                maxB = max(maxB,ps[i].second);
            }
        }
        hull.add(FN(currSlope,maxB));
        /*
        int prevSlope = -5005;
        ll maxB = -1e18;
        ll minB = 1e18;
        for (auto p: ps) {
            if (p.second != prevSlope) {
                if (prevSlope != -5005) {
                    hull.add(FN(prevSlope,maxB));
                    hull.add(FN(-prevSlope,minB));
                }
                prevSlope = p.second;
                maxB = p.first;
                minB = p.first;
            }
            else {
                maxB = max(maxB,p.first);
                minB = min(minB,p.first);
            }
        }
        hull.add(FN(prevSlope,maxB));
        hull.add(FN(-prevSlope,minB));
        */
        /*
        for (auto p: hullNeg) {
            cout << p.b << ' ' << p.m << '\n';
        }
        */
    }
    ll getmax() { //returns max of block
        return hull.query(x);
    }
} blocks[maxn];

void ADD(int l, int r, int x) {
    /*
    for (int i = l; i <= r; i++) {
        a[i] += x;
    }
    */
    int orig = l;
    while (l != 0 && bucket[l] == bucket[l-1] && l <= r) {
        a[l] += x;
        l++;
    }
    if (l-1 >= 0) blocks[bucket[l-1]].refresh();
    while (l <= r && bucket[l] < bucket[r]) {
        blocks[bucket[l]].x += x;
        l += BLK;
    }
    while (l <= r) {
        a[l] += x;
        l++;
    }
    if (bucket[orig] != bucket[r]) blocks[bucket[r]].refresh();
}

ll QUERY(int l, int r) {
    ll res = 0;
    /*
    for (int i = l; i <= r; i++) {
        res = max(res,abs(a[i]+blocks[bucket[i]].x)*b[i]);
    }
    return res;
    */
    while (l != 0 && bucket[l] == bucket[l-1] && l <= r) {
        res = max(res,abs((a[l]+blocks[bucket[l]].x)*b[l]));
        l++;
    }
    while (l <= r && bucket[l] < bucket[r]) {
        res = max(res,blocks[bucket[l]].getmax());
        l += BLK;
    }
    while (l <= r) {
        res = max(res,abs((a[l]+blocks[bucket[l]].x)*b[l]));
        l++;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    BLK = max(10,(int)sqrt(n)/2);
    for (int i = 2; i <= n; i++) {
        int pi; cin >> pi;
        adj[pi].push_back(i);
    }
    DFS(1); 
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        a[tin[i]] += ai;
        a[tout[i]+1] -= ai;
    }
    for (int i = 1; i <= n; i++) {
        int bi; cin >> bi;
        b[tin[i]] += bi;
        b[tout[i]+1] -= bi;
    }
    for (int i = 1; i <= n; i++) {
        a[i] += a[i-1];
        b[i] += b[i-1];
    }
    for (int i = 0; i < n; i++) {
        //printf("%d: a = %d, b = %d\n",i,a[i],b[i]);
        b[i] = abs(b[i]);
    }
    //sqrt decomposition
    for (int i = 0; i < n; i++) {
        bucket[i] = i/BLK;
        blocks[bucket[i]].indices.push_back(i);
        if (i == 0 || bucket[i] != bucket[i-1]) {
            blocks[bucket[i]].start = i;
        }
    }
    for (int i = 0; i <= bucket[n-1]; i++) {
        blocks[i].setup();
    }

    while (q--) {
        int t, v; cin >> t >> v;
        if (t == 1) {
            int x; cin >> x;
            ADD(tin[v],tout[v],x);
        }
        else {
            cout << QUERY(tin[v],tout[v]) << endl;
        }
    }
}

