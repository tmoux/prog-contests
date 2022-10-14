#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

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

const ll INF = 1e18;
struct Tracker {
  set<pair<int, int>> s;
  map<int, int> mp;

  void add(int c, int x) {
    if (!mp.count(c)) {
      mp[c] = x;
      s.insert({x, c});
    }
    else {
      s.erase({mp[c], c});
      ckmax(mp[c], x);
      s.insert({mp[c], c});
    }
  }

  int getr(int c) {
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
      if (it->second != c) return it->first;
    }
    return -INF;
  }
};

void solve() {
  int N; cin >> N;
  vector<array<int, 4>> v(N);
  F0R(i, N) {
    cin >> v[i][0] >> v[i][1] >> v[i][2];
    v[i][3] = i;
  }
  vector<int> ans(N, INF);

  auto f = [&]() -> void {
    auto starts = v;
    auto ends = v;
    sort(all(starts), [&](auto a, auto b) {
        return a[0] < b[0];
        });
    sort(all(ends), [&](auto a, auto b) {
        return a[1] < b[1];
        });
    Tracker tracker;
    int i = 0;
    for (auto [l, r, c, id]: ends) {
      while (i < sz(starts) && starts[i][0] <= r) {
        tracker.add(starts[i][2], starts[i][1]);
        i++;
      }
      ckmin(ans[id], max(0LL, l - tracker.getr(c)));
    }
  };

  f();
  F0R(i, N) {
    int l = v[i][0];
    int r = v[i][1];
    v[i][0] = -r;
    v[i][1] = -l;
  }
  f();

  F0R(i, N) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}
