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
  int N, K; cin >> N >> K;
  vector<array<ll, 3>> A(N);
  F0R(i, N) {
    cin >> A[i][1];
  }
  F0R(i, N) {
    cin >> A[i][2];
  }
  F0R(i, N) {
    A[i][0] = 1LL * A[i][1] * A[i][2];
  }
  sort(all(A));
  // cout << A << endl;

  auto closestR = [&](ll x, ll f) -> ll {
    return f * ((x + f - 1) / f);
  };
  int ans = N;
  for (int r = 0; r < N; r++) {
    vector<pair<ll, int>> v;
    F0R(i, N) {
      v.push_back({closestR(A[r][0], A[i][1]), i});
    }
    sort(all(v));
    int l = r;
    ll L = A[r][0];
    while (!v.empty()) {
      ll x = v.back().first;
      while (l > 0 && x - A[l-1][0] <= K) l--;
      if (x - min(L, A[l][0]) <= K) {
        // update ans
        ckmin(ans, N - (r - l + 1));
      }

      // update for next
      while (!v.empty() && v.back().first == x) {
        auto [_, i] = v.back(); v.pop_back();
        ll y = x - A[i][1];
        if (y <= 0) goto done;
        ckmin(L, y);
      }
    }
    done:;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
