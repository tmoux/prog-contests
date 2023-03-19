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

struct LeftTracker {
  ll total = 0;
  vector<int> v;
  int cur = 0;

  void insert(int x, int d) {
    if (d == 1) total++;
    v.push_back(x);
    if (sz(v) == 1) {
      cur = 0;
    }
    else if (sz(v) % 2 == 0) {
      total += x - v[cur];
    }
    else {
      total += x - v[cur];
      total -= v[cur+1] - v[cur];
      cur++;
    }
  }
};

struct RightTracker {
  ll total = 0;
  vector<array<int, 2>> v;
  int cur = 0;
  int size = 0;

  RightTracker(vector<array<int, 2>> _v) {
    v = _v;
    cur = sz(v) / 2;
    for (auto [x, d]: v) {
      if (d == 0) total++;
      total += abs(v[cur][0] - x);
    }
    size = sz(v);
  }

  void del(int x, int d) {
    if (d == 0) total--;
    total -= v[cur][0] - x;
    size--;
    if (size % 2 == 0) cur++;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<array<int, 2>> Xs(N), Ys(N);
  F0R(i, N) {
    int x, y, v; cin >> x >> y >> v;
    Xs[i][0] = x;
    Xs[i][1] = !(v == 0 || v == 1);
    Ys[i][0] = y;
    Ys[i][1] = !(v == 0 || v == 3);
  }

  auto solve = [&](vector<array<int, 2>> v) -> ll {
    sort(all(v));
    LeftTracker lt;
    RightTracker rt(v);

    ll ans = 0;
    int t = v[sz(v) / 2][0];
    for (auto [x, d]: v) {
      ans += abs(x - t);
    }

    for (auto [x, d]: v) {
      lt.insert(x, d);
      rt.del(x, d);

      ckmin(ans, lt.total + rt.total);
    }
    return ans;
  };

  ll ans = solve(Xs) + solve(Ys);
  cout << ans << '\n';
}