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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<int> ans(M+1, -1);
  vector<int> poss(M+1, 0); poss[0] = 1;
  F0R(tt, N) {
    int t, y;
    ll xx;
    cin >> t >> xx >> y;
    auto add = [&](ll k) -> ll {
      return k + (xx + 100000 - 1) / 100000;
    };
    auto mult = [&](ll k) -> ll {
      return (1LL * k * xx + 100000 - 1) / 100000;
    };
    vector<int> cur(M+1, 0);
    F0R(i, M+1) if (poss[i]) cur[i] = y;
    F0R(i, M+1) {
      if (cur[i] > 0) {
        ll ni = t == 1 ? add(i) : mult(i);
        if (ni <= M) {
          poss[ni] = 1;
          ckmax(cur[ni], cur[i] - 1);
        }
      }
    }

    FOR(i, 1, M+1) {
      if (poss[i] && ans[i] == -1) {
        ans[i] = tt+1;
      }
    }
  }

  FOR(i, 1, M+1) {
    cout << ans[i] << " \n"[i == M];
  }

  // double k = 1;
  // double x = 1.05;
  // REP(50) {
  //   k = ceil(k * x);
  //   cout << fixed << setprecision(5) << k << endl;
  // }
}
