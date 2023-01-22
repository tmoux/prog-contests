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

int solve() {
  int N; cin >> N;
  vector<int> A(N), B(N);
  F0R(i, N) cin >> A[i];
  F0R(i, N) cin >> B[i];
  using vi = vector<int>;
  vector<pair<vi, vi>> groups = {{A, B}};

  auto check = [&](const pair<vi, vi>& p, int d) -> std::optional<array<pair<vi, vi>, 2>> {
    auto& [v1, v2] = p;
    vi X[2], Y[2];
    for (auto x: v1) {
      X[(x >> d) & 1].push_back(x);
    }
    for (auto x: v2) {
      Y[(x >> d) & 1].push_back(x);
    }
    if (sz(X[0]) == sz(Y[1])) {
      array<pair<vi, vi>, 2> ret;
      ret[0] = {X[0], Y[1]};
      ret[1] = {X[1], Y[0]};
      return ret;
      // = {{X[0], Y[1]}, {X[1], Y[0]}};
      // return ret;
    }
    else {
      return std::nullopt;
    }
  };
  int ans = 0;
  F0Rd(d, 30) {
    vector<pair<vi, vi>> ng;
    bool poss = true;
    for (auto& p: groups) {
      auto r = check(p, d);
      if (r) {
        auto [nv1, nv2] = *r;
        if (!nv1.first.empty()) ng.push_back(nv1);
        if (!nv2.first.empty()) ng.push_back(nv2);
      }
      else {
        poss = false;
        break;
      }
    }

    if (poss) {
      ans += 1 << d;
      groups = ng;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
