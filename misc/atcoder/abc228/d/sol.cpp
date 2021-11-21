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

int mult(int a, int b, MOD) {
    return (1LL*a*b) % MOD;
}
int modexp(int a, int b, int MOD) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a,MOD);
        a = mult(a,a,MOD);
        b >>= 1;
    }
    return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  const int N = 1<<20;
  map<int, ll> s;
  set<int> open;
  F0R(i, N) open.insert(i);
  int Q; cin >> Q;
  while (Q--) {
    int t;
    ll xi;
    cin >> t >> xi;
    int x = xi % N;

    if (t == 1) {
      auto it = open.lower_bound(x);
      if (it != open.end()) {
        s[*it] = xi;
      }
      else {
        it = open.begin();
        s[*it] = xi;
      }
      open.erase(it);
    }
    else if (t == 2) {
      if (s.count(x)) {
        cout << s[x] << '\n';
      }
      else cout << -1 << '\n';
    }
  }
}
