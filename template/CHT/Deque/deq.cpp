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
    void addFN(const FN& l) {
        while (size() >= 2 && 
            comp((*this)[size()-2],(*this)[size()-1],l)) {
            this->pop_back();    
        }
        this->push_back(l);
    }

    ll query(ll x) {
        if (size() == 0) return -(1LL<<62); //handle empty hull
        while (size() >= 2 && (*this)[1].eval(x) >= (*this)[0].eval(x)) {
            pop_front();
        }
        return (*this)[0].eval(x);
    }
};
