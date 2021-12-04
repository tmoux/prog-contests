#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

namespace std {
  template<class Fun>
    class y_combinator_result {
      Fun fun_;
      public:
      template<class T>
        explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

      template<class ...Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template<class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
} // namespace std

// }}}

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

ll solve() {
  int N; cin >> N;
  vector<ll> a(N);
  for (auto& i: a) cin >> i;
  vector<ll> dp(N, 0LL);
  Hull hull; //negated lines
  for (int i = 0; i < N; i++) {
    if (i > 0) {
      dp[i] = -hull.query(i) - a[i];
    }
    // add line
    hull.addFN(FN(-a[i], -(dp[i] - a[i]*(i-1))));
  }

  ll ans = dp[N-1];
  return max(ans, 0LL);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
