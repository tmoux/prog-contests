#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

void solve() {
  int K; cin >> K;
  int N = 1 << (K+1);
  vector<int> V(N+1);
  F0R(i, N) {
    cin >> V[i+1];
  }
  bool poss = 0;
  int C = 0;
  vector<int> cnt(4, 0);
  FOR(a, 0, 2*K) {
    FOR(b, a+1, 2*K) {
      F0R(i, N+1) {
        int x = (V[i] >> a) & 1;
        int y = (V[i] >> b) & 1;
        cnt[2*x+y]++;
      }
      F0R(mask, 4) {
        if (cnt[mask] >= (1 << K)) {
          poss = 1;
        }
      }
    }
  }
  // FOR(i, 0, N+1) {
  //   FOR(j, i+1, N+1) {
  //     FOR(k, j+1, N+1) {
  //       FOR(l, k+1, N+1) {
  //         if ((V[i] ^ V[j] ^ V[k] ^ V[l]) == 0) {
  //           poss = 1;
  //           C++;
  //           // goto done;
  //         }
  //       }
  //     }
  //   }
  // }
  // F0R(i, N) {
  //   int x = 0;
  //   FOR(j, i, N) {
  //     x ^= V[j];
  //     FOR(k, j+1, N) {
  //       int y = 0;
  //       FOR(l, k, N) {
  //         y ^= V[l];
  //         if (x == y) {
  //           poss = true;
  //           goto done;
  //         }
  //       }
  //     }
  //   }
  // }
  done:
  DEBUG(C);
  if (poss) {
    cout << "ok\n";
  }
  else assert(false);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
