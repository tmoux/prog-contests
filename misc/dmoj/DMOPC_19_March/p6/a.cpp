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
//insert, delete, and query in O(log n)
struct Hull: public set<FN> //convex hull for maximum
{
    void addFN(FN fn) {
        Hull::iterator it = lower_bound(fn);
        if (it != end() && it->m == fn.m) {
            if (it->b >= fn.b) return; //no need to consider it
            //this line must be changed based on +/- slope!!!
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
        if (this->empty()) return 0; //because querying for maximum
        auto it = lower_bound(FN(x,0,true));
        return it->eval(x);
    }
};

const int maxn = 200005;
int N, M, D;
ll v[maxn], suf[maxn], sum[maxn];
int l[maxn], r[maxn];
int a[maxn], d[maxn];
ll ans[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
    Hull hull;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
        hull.clear();
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

	void add(int st, int en, FN fn) {
		if (st <= s && e <= en) {
            hull.addFN(fn);
            return;
		}
		if (st <= m) {
            assert(l);
            l->add(st,en,fn);
		}
		if (en > m) {
            assert(r);
            r->add(st,en,fn);
		}
	}

	ll getsum(int i, int x) {
		if (s == e) {
            return hull.query(x);
		}
		ll ret = hull.query(x);
		if (i <= m) {
            assert(l);
			ret = max(ret,l->getsum(i,x));
		}
        else {
            assert(r);
			ret = max(ret,r->getsum(i,x));
		}
		return ret;
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> D;
    for (int i = 1; i <= M; i++) {
        cin >> v[i] >> l[i] >> r[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> a[i] >> d[i];
    }
    for (int i = M; i >= 1; i--) {
        suf[i] = v[i] + suf[i+1];
    }
    for (int i = M; i >= 1; i--) {
        sum[i] = sum[i+1]+suf[i+1]+v[i];
    }
    bool sub3 = true;
    for (int i = 1; i <= M; i++) {
        if (l[i] != 1 || r[i] != D) {
            sub3 = false;
            break;
        }
    }
    if (false /*N <= 5000*/) {
        for (int i = 1; i <= N; i++) {
            //cout << i << ":\n";
            ll penalty = 0;
            ll mx = 0;
            for (int j = a[i]+1; j <= M; j++) {
                penalty += (j-a[i])*v[j];
                if (l[j] <= d[i] && d[i] <= r[j]) {
                    //cout << j << ": " << ((j-a[i])*v[j]+suf[j+1]) << '\n';
                    mx = max(mx,(j-a[i])*v[j]+suf[j+1]);
                }
            }
            //cout << "penalty: " << penalty << endl;
            cout << (penalty-mx) << '\n';
        }
    }
    else if (false /*sub3*/) {
        Hull hull;
        vector<pair<pair<int,int>,int>> vv;
        for (int i = 1; i <= N; i++) {
            vv.push_back({{a[i],d[i]},i});
        }
        sort(vv.begin(),vv.end(),[](auto a, auto b) {
                return a.first.first > b.first.first;
                });
        int j = M;
        for (auto p: vv) {
            int id = p.second;
            int ai = p.first.first;
            while (ai < j) {
                hull.addFN(FN(-v[j],j*v[j]+suf[j+1]));
                --j;
            }
            ans[id] = sum[ai+1] - hull.query(ai);
            //cout << ai << ": " << sum[ai+1] << '\n';
            /*
            for (auto fn: hull) {
                cout << "line: " << fn.m << ' ' << fn.b << '\n';
            }
            */
            //cout << ai << ' ' << hull.query(ai) << '\n';
            //cout << '\n';
        }
        for (int i = 1; i <= N; i++) {
            cout << ans[i] << '\n';
        }
    }
    else {
        //subtask 4
        Node *root = new Node(1,D);
        vector<pair<pair<int,int>,int>> vv;
        for (int i = 1; i <= N; i++) {
            vv.push_back({{a[i],d[i]},i});
        }
        sort(vv.begin(),vv.end(),[](auto a, auto b) {
                return a.first.first > b.first.first;
                });
        int j = M;
        for (auto p: vv) {
            int id = p.second;
            int ai = p.first.first;
            int i = p.first.second;
            while (ai < j) {
                FN fn = FN(-v[j],j*v[j]+suf[j+1]);
                root->add(l[j],r[j],fn);
                --j;
            }
            ans[id] = sum[ai+1] - root->getsum(i,ai);
        }
        for (int i = 1; i <= N; i++) {
            cout << ans[i] << '\n';
        }
    }
}

