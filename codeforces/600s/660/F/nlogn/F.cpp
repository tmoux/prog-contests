#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const int maxn = 2e5+5;
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
    void addFront(const FN& l) {
        //slopes coming in -1,-2,-3,...so add to front of deque rather than back (querying for maximum)
        while (this->size() >= 2 && 
            comp(l,(*this)[0],(*this)[1])) {
            this->pop_front();    
        }
        this->push_front(l);
    }

    ll query(ll x) {
        return hullSearch(x,*this,0,this->size()-1);        
    }

    friend ll hullSearch(ll x, const Hull& hull, int lo, int hi) {
        //queries for maximum
        //O(log n)
        //searches [lo, hi] in hull
        if (hull.size() == 1) return hull.front().eval(x);
        if (lo == hi) return hull[lo].eval(x);
        if (x <= hull[lo].intersect(hull[lo+1])) return hull[lo].eval(x);
        if (x >= hull[hi].intersect(hull[hi-1])) return hull[hi].eval(x);
        while (lo + 1 < hi) {
            int m = (lo+hi)/2;
            ll x1 = (ll)hull[m].intersect(hull[m-1]);
            ll x2 = (ll)hull[m].intersect(hull[m+1]);
            if (x1 <= x && x <= x2) return hull[m].eval(x);
            if (x < x1) hi = m;
            else lo = m;
        }
        return hull[lo].eval(x);
    }
};

int N;
ll S1[maxn], S2[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        cin >> S1[i];
        S2[i] = S2[i-1] + (ll)i*S1[i];
        S1[i] += S1[i-1]; 
        ans = max(ans,S2[i]);
    }
    Hull hull;
    for (int L = 1; L <= N; L++) {
        ll m = 1-L;
        ll b = (L-1)*S1[L-1] - S2[L-1];
        hull.addFront(FN(m,b));
        ll r = hull.query(S1[L]) + S2[L];
        ans = max(ans,r);
    }
    cout << ans << '\n';

    return 0;
}

