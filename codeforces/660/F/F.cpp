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
        assert(m != r.m);
        return (ld)(r.b-b)/(ld)(m-r.m);
    }

    friend bool comp(const FN& l1, const FN& l2, const FN& l) {
    	//order in deque: l1, l2, l
    	//true --> l2 is unnecessary
    	ll c1 = (l2.b-l1.b) * (l2.m-l.m);
    	ll c2 = (l2.b-l.b) * (l2.m-l1.m);
        return c1 >= c2;
    }
};

struct Hull: public deque<FN> //convex hull for maximum
{
    void addBack(const FN& l) {
        while (this->size() >= 2 && 
            comp((*this)[this->size()-2],(*this)[this->size()-1],l)) {
            this->pop_back();    
        }
        this->emplace_back(l);
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
ll a[maxn], pfx[maxn];
ll x[maxn], C[maxn], b[maxn];

ll f(int l, int r) {
    if (l > r) return 0;
    if (l == r) return max(0LL,a[l]); 
    int mid = (l+r)>>1;
    ll res = max(f(l,mid),f(mid+1,r));
    for (int i = l-1; i <= r+1; i++) {
        x[i] = 0;
        C[i] = 0;
        b[i] = 0;
    }
    for (int i = mid+1; i <= r; i++) {
        x[i] = x[i-1] + a[i];
        C[i] = C[i-1] + a[i]*(i-mid);
    }
    Hull hull;
    for (int L = mid; L >= l; L--) {
        b[L] = b[L+1] + (pfx[mid]-pfx[L-1]);
        //cout << "b " << L << "= " << b[L] << '\n';
        ll m = mid-L+1;
        FN line = FN(m,b[L]);
        hull.addBack(line);
    }
    for (int R = mid + 1; R <= r; R++) {
        res = max(res,hull.query(x[R]) + C[R]);
    }
    return res;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    scanf("%d\n",&N);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        //cout << a[i] << '\n';
        pfx[i] = a[i] + pfx[i-1];
    }
    cout << f(1,N) << '\n';
    return 0;
}

