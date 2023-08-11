#include <bits/stdc++.h>
using namespace std;
using ll = long long;

typedef long double ld;

const ld eps = 1e-9;
struct FN
{
    ll m, b; //in this case, function is a line
    FN(ll _m, ll _b) : m(_m), b(_b) {}
    ld eval(ld x) const {
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

struct HullMax: public deque<FN> //convex hull for maximum
{
    void add(const FN& l) {
        while (size() >= 2 && 
            comp((*this)[size()-2],back(),l)) {
            this->pop_back();    
        }
        this->push_back(l);
    }

    ld query(ld x) {
        while (size() >= 2 && front().eval(x) <= (*this)[1].eval(x)+eps) {
            this->pop_front();
        }
        return front().eval(x);
    }

    ld getIntersection() {
        assert(size() >= 2);
        return front().intersect((*this)[1]);
    }
};

struct HullMin: public deque<FN> //convex hull for min
{
    void add(const FN& l) {
        while (size() >= 2 && 
            comp((*this)[size()-2],back(),l)) {
            this->pop_back();    
        }
        this->push_back(l);
    }

    ld query(ld x) {
        while (size() >= 2 && front().eval(x) >= (*this)[1].eval(x)-eps) {
            this->pop_front();
        }
        return front().eval(x);
    }

    ld getIntersection() {
        assert(size() >= 2);
        return front().intersect((*this)[1]);
    }
};

const int maxn = 2e5+5;
int n;
ll b[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        b[i] += b[i-1];
    }
    HullMax top;
    HullMin bot;
    for (int i = n; i >= 0; i--) {
        top.add(FN(-i,b[i]));
    }
    for (int i = 0; i <= n; i++) {
        bot.add(FN(-i,b[i]));
    }
    ld ans = 1e50;
    while (top.size() >= 2 || bot.size() >= 2) {
        //cout << top.size() << ' ' << bot.size() << endl;
        if (top.size() < 2) {
            ld x = bot.getIntersection();
            ans = min(ans,top.query(x)-bot.query(x));
        }
        else if (bot.size() < 2) {
            ld x = top.getIntersection();
            ans = min(ans,top.query(x)-bot.query(x));
        }
        else {
            ld x1 = top.getIntersection();
            ld x2 = bot.getIntersection();
            if (x1 < x2) {
                ans = min(ans,top.query(x1)-bot.query(x1));
            }
            else {
                ans = min(ans,top.query(x2)-bot.query(x2));
            }
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
}
