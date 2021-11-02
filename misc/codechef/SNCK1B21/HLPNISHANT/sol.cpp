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

  template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v)
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

ll solve(ll K) {
  ll lo = 0, hi = K+1;
  while (lo + 1 < hi) {
    ll mid = (lo+hi)/2;
    if (mid*(mid-1)/2 < K) {
      lo = mid;
    }
    else hi = mid;
  }

  return 2*lo;
}

int brute(ll K) {
  vector<int> v;
  int cur = K;
  for (int sub = 1; cur >= 1; sub++) {
    v.push_back(cur);
    cur -= sub;
  }
  return 2*sz(v);
  //cout << 2*sz(v) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  /*
  for (int k = 2; k <= 100; k++) {
    auto a = solve(k);
    auto b = brute(k);
    cout << k << ": " << solve(k) << ' ' << brute(k) << endl;
    assert(a == b);
  }
  */
  int T; cin >> T;
  while (T--) {
    int K; cin >> K;
    cout << solve(K) << '\n';
  }
}
