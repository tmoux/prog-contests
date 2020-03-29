#include <bits/stdc++.h>
using namespace std;
using ll = long long;

typedef long double ld;
const ll INF = 1LL<<62;
struct FN
{
    ll m, b; //in this case, function is a line
    bool is_query;
    FN(ll _m, ll _b, bool is = false) : m(_m), b(_b), is_query(is) {}
    mutable function<ld()> xRight; //right intersection point of line in hull, is infinity for rightmost line
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

    bool operator<(const FN& rhs) const {
        //make sure to check which </> should be used
        if (!rhs.is_query) return m < rhs.m;
        ll x = rhs.m;
        return xRight() < (ld)x;
    }
};

//goal: dynamic variant of convex hull
//insert and query in O(log n)
struct Hull: public set<FN> //convex hull for maximum
{
    void addFN(FN fn) {
        Hull::iterator it = lower_bound(fn);
        if (it != end() && it->m == fn.m) {
            if (it->b >= fn.b) return; //no need to consider it
            erase(it);
        }
        it = insert(fn).first;
        //check if what we just inserted is necessary
        if (it != begin() && next(it) != end()) {
            if (comp(*prev(it),*it,*next(it))) {
                //not needed
                erase(it);
                return;
            }
        }
        it->xRight = [=] { return next(it) == end() ? INF : it->intersect(*next(it)); };
        //function pointer magic
        //Removes unnecessary lines above and below
        Hull::iterator b1, b2, f1, f2;
        while (true) {
            if (it == begin()) break;
            else {
                b1 = prev(it);
                if (b1 == begin()) break;
                else {
                    b2 = prev(b1);
                    if (comp(*b2,*b1,*it)) {
                        erase(b1);
                    }  
                    else break;     
                }
            }
        }
        while (true) {
            f1 = next(it);
            if (f1 == end()) break;
            else {
                f2 = next(f1);
                if (f2 == end()) break;
                else {
                    if (comp(*it,*f1,*f2)) {
                        erase(f1);
                    }
                    else break;
                }
            }
        }
    }

    ll query(ll x) {
        if (this->empty()) return -INF; //because querying for maximum
        auto it = lower_bound(FN(x,0,true));
        return it->eval(x);
    }
};

const int maxn = 80005;
int N, Q;
int A[maxn], B[maxn], C[maxn];

int tin[maxn], tout[maxn], t = 0;
vector<int> adj[maxn];

void dfs(int i, int p) {
    tin[i] = t++;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
    tout[i] = t-1;
}

ll ans[160005];

struct Node {
	int s, e, m;
	//covers s,e;
    Hull hull;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
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

	void add(int st, int en, int a, int b) {
		if (st <= s && e <= en) {
            hull.addFN(FN(-b,-a));
            return;
		}
		if (st <= m) {
            l->add(st,en,a,b);
		}
		if (en > m) {
            r->add(st,en,a,b);
		}
	}

	ll getsum(int i, ll x) {
        ll ret = hull.query(x);
		if (s == e && s == i) {
            return ret;
		}
		if (i <= m) {
			ret = max(ret,l->getsum(i,x));
		}
        else {
            ret = max(ret,r->getsum(i,x));
		}
		return ret;
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> B[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> C[i];
    }
    for (int i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    vector<pair<pair<int,int>,int>> v;
    for (int i = 0; i < Q; i++) {
        int V, T; cin >> V >> T;
        v.push_back({{V,T},i});
    }
    sort(v.begin(),v.end(),[](auto a, auto b) {
            return a.first.second < b.first.second;
            });
    //segtree
    Node *root = new Node(0,N);
    //pop from back
    vector<pair<int,int>> nod;
    for (int i = 1; i <= N; i++) {
        nod.push_back({i,C[i]});
    }
    sort(nod.begin(),nod.end(),[](auto a, auto b) {
            return a.second < b.second;
            });
    //cout << "sq = " << sq << endl;
    while (!v.empty()) {
        auto p = v.back(); v.pop_back();
        int V = p.first.first;
        int T = p.first.second;
        //cout << "doing " << V << ' ' << T << '\n';
        int id = p.second;
        while (!nod.empty() && nod.back().second >= T) {
            //add the node
            auto q = nod.back(); nod.pop_back();
            int i = q.first;
            int a = A[i];
            int b = B[i];
            //cout << "adding " << tin[i] << ' ' << tout[i] << ' ' << a << ' ' << b << '\n';
            root->add(tin[i],tout[i],a,b);
        }
        //answer query
        ll res = -root->getsum(tin[V],T);
        //cout << res << '\n';
        ans[id] = res;
    }
    for (int i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }
}
