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
  int N; cin >> N;
  vector<int> P(N), Q(N);
  vector<int> ppos(N), qpos(N);
  F0R(i, N) {
    cin >> P[i], P[i]--;
    ppos[P[i]] = i;
  }
  F0R(i, N) {
    cin >> Q[i], Q[i]--;
    qpos[Q[i]] = i;
  }

  auto ways = [](int x) {
    return 1LL * x * (x + 1) / 2;
  };


  const int INF = 1e9;
  int l1 = INF, r1 = -INF;
  int l2 = INF, r2 = -INF;

  ll ans = 0;
  for (int mex = 0; mex < N; mex++) {
    int i = ppos[mex], j = qpos[mex];
    if (i > j) swap(i, j);

    if (mex == 0) {
      ans += ways(i);
      ans += ways(max(0, j - i - 1));
      ans += ways(N - 1 - j);
    }
    else {
      int L = min(l1, l2), R = max(r1, r2);
      int lcnt = 0, rcnt = 0;
      if (R < i) {
        lcnt = L + 1, rcnt = i - R;
      }
      else if (i < L && R < j) {
        lcnt = L - i, rcnt = j - R;
      }
      else if (L > j) {
        lcnt = L - j, rcnt = N - R;
      }
      ans += 1LL * lcnt * rcnt;
    }

    ckmin(l1, ppos[mex]);
    ckmax(r1, ppos[mex]);
    ckmin(l2, qpos[mex]);
    ckmax(r2, qpos[mex]);
  }
  ans += 1;

  cout << ans << '\n';
}
