#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//so my brute force is correct, my hull is wrong

const int maxn = 1e5+5;
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
        if (!rhs.is_query) return m > rhs.m;
        //greater since we want smaller slopes to the right
        ll x = rhs.m;
        return xRight() < (ld)x; //always stays the same
    }
};

//goal: dynamic variant of convex hull
//insert, delete, and query in O(log n)
struct Hull: public set<FN> //convex hull for maximum
{
    void addFN(FN fn) {
        Hull::iterator it = lower_bound(fn);
        if (it != end() && it->m == fn.m) {
            if (it->b <= fn.b) return; //no need to consider it
            //this line must be changed based on +/- slope!!!
            //min-neg --> <=
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
        //if (this->empty()) return 0; //because querying for maximum
        assert(!this->empty());
        auto it = lower_bound(FN(x,0,true));
        return it->eval(x);
    }
};


//dp[i] = min_{1 <= j < i} (h[i]-h[j])^2 + sum(w[j+1]..w[i-1]) + dp[j]
// = (h[i]-h[j])^2 + pfx[i-1]-pfx[j]+dp[j]
// = h[i]^2 - 2h[i]*h[j] + h[j]^2 + pfx[i-1] - pfx[j] + dp[j]
// = (h[i]^2+pfx[i-1]) + (-2h[j])*h[i] + (dp[j]-pfx[j]) + h[j]^2
// =  (independent)    + (mx)          -      b 
// So each j has (m,b) = (-2h[j],dp[j]-pfx[j]+h[j]^2)
// Unfortunately, the h[i]'s and h[j]'s aren't monotonic, so we have implement a hull w/ dynamic 
// queries/insertions
//

int n;
ll h[maxn], w[maxn], pfx[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        pfx[i] = w[i] + pfx[i-1];
    }
    Hull hull;
    hull.addFN(FN(-2*h[1],-pfx[1]+h[1]*h[1]));
    for (int i = 2; i <= n; i++) {
        ll q = hull.query(h[i]) + (h[i]*h[i])+pfx[i-1];
        /*
        cout << hull.query(h[i]) << '\n';
        cout << i << ": " << q << '\n';
        */
        hull.addFN(FN(-2*h[i],q-pfx[i]+h[i]*h[i]));
        if (i == n) {
            cout << q << '\n';
        }
    }
}

