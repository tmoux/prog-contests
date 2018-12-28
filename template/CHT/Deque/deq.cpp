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
    void addFront(const FN& l) {
        //slopes coming in -1,-2,-3,...so add to front of deque rather than back (querying for maximum)
        //if adding to back, need to change the indices
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