#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const int maxn = 2e5+5;
const ll INF = 1LL<<62;
struct FN
{
    ll m, b; //in this case, function is a line
    bool is_query;
    FN(ll _m, ll _b, bool is = false) : m(_m), b(_b), is_query(is) {}

    mutable function<ld()> xRight;
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
            erase(it);
        }
        it = insert(fn).first;
        it->xRight = [=] { return next(it) == end() ? INF : it->intersect(*next(it)); };
        while (true) {
            if (it == begin()) break;
            else {
                Hull::iterator b1 = prev(it,1);
                if (b1 == begin()) break;
                else {
                    Hull::iterator b2 = prev(b1,1);
                    if (comp(*b2,*b1,*it)) {
                        erase(b1);
                    }  
                    else break;     
                }
            }
        }
        
        while (true) {
            Hull::iterator f1 = next(it,1);
            if (f1 == end()) break;
            else {
                Hull::iterator f2 = next(f1,1);
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
        /*
        ll res = NINF;
        for (FN fn: *this) {
            res = max(res,fn.eval(x));
            printf("y = %dx + %d: %d\n",fn.m,fn.b,fn.eval(x));
        }
        printf("x = %d: ans = %d\n\n",x,res);
        return res;
        */
        
        auto it = lower_bound(FN(x,0,true));
        assert(it != end());
        //cout << it->m << ' ' << it->b << '\n';
        //cout << it->eval(x) << '\n';

        //printf("Line chosen: y = %dx + %d\n",it->m,it->b);
        //cout << x << ": " << it->eval(x) << '\n';
        return it->eval(x);
        
    }
};

int N;
ll S1[maxn], S2[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        cin >> S1[i];
        S2[i] = S2[i-1] + (ll)i*S1[i];
        S1[i] += S1[i-1]; 
        //ans = max(ans,S2[i]);
    }
    Hull hull;
    for (int L = 1; L <= N; L++) {
        ll m = 1-L;
        ll b = (L-1)*S1[L-1] - S2[L-1];
        hull.addFN(FN(m,b));
        /*
        for (FN fn: hull) {
            printf("y = %dx + %d\n",fn.m,fn.b);
            //cout << fn.m << ' ' << fn.b << '\n';
            cout << fn.xLeft() << '\n';
        }
        cout << "-----\n";
        */
        ll r = hull.query(S1[L]) + S2[L];
        ans = max(ans,r);
    }
    cout << ans << '\n';

    return 0;
}

