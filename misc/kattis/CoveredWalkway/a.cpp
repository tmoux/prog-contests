#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1LL<<62;
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

struct Hull: public deque<FN> //convex hull for minimum
{
    void addBack(const FN& l) {
        
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
        
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, c; cin >> n >> c;
    vector<ll> a(n+1);
    for (int i = 1; i <= n; i++) {
    	cin >> a[i];
    }
    Hull hull;
    hull.addBack(FN(-2*a[1],a[1]*a[1]));
    ll ans;
    for (int i = 1; i <= n; i++) {
    	ll dpi = hull.query(a[i]) + a[i]*a[i] + c;
    	ll m = -2*a[i+1];
    	ll b = dpi + a[i+1]*a[i+1];
    	hull.addBack(FN(m,b));
        ans = dpi;
    }
    cout << ans << '\n';

    return 0;
}
