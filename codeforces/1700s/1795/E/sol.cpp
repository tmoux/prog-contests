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

struct Tracker {
  vector<pair<int, int>> s;
  ll total = 0;

  Tracker(int x) {
    s.emplace_back(x, 1);
  }

  int max_height() {
    return s.back().first;
  }

  void merge() {
    while (true) {
      auto [x, l] = s.back(); s.pop_back();
      if (s.empty() || s.back().first < x - l) {
        s.emplace_back(x, l);
        break;
      }
      else {
        assert(s.back().first == x - l);
        auto [_, l2] = s.back(); s.pop_back();
        s.emplace_back(x, l + l2);
      }
    }
  }

  void decr(int D) {
    if (D == 0) return;
    auto [x, l] = s.back(); s.pop_back();
    if (!s.empty()) {
      int d = min(x - l - s.back().first, D);
      total += 1LL * d * l;
      s.emplace_back(x - d, l);
      merge();
      decr(D - d);
    }
    else if (x == l) {
      assert(D <= x);
      total += 1LL * D * (D + 1) / 2 + 1LL * D * (l - D);
      s.emplace_back(x - D, x - D);
    }
    else {
      int d = min(D, x-l);
      total += 1LL * d * l;
      s.emplace_back(x - d, l);
      decr(D - d);
    }
  }

  void insert(int x) {
    int D = max(0, s.back().first - (x - 1));
    decr(D);
    s.emplace_back(x, 1);
    merge();
  }
};

void solve() {
  int N; cin >> N;
  vector<ll> H(N);
  F0R(i, N) {
    cin >> H[i];
  }

  vector<ll> ans = H;
  Tracker tracker(H[0]);
  for (int i = 1; i < N; i++) {
    tracker.insert(H[i]);
    ans[i] += tracker.total;
  }
  tracker = Tracker(H[N-1]);
  for (int i = N-2; i >= 0; i--) {
    tracker.insert(H[i]);
    ans[i] += tracker.total;
  }

  cout << *min_element(all(ans)) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
