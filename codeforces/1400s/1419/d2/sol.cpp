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
  vector<int> a(N);
  for (auto& x: a) cin >> x;
  sort(all(a));

  vector<int> ans = a;
  auto check = [&](int X) -> bool {
    vector<int> b(N, -1);
    deque<int> d;
    F0R(i, X) {
      if (i*2 + 1 >= N) return false;
      if (i % 2 == 0) d.push_back(a[i]);
      else d.push_front(a[i]);
    }
    F0R(i, X) {
      b[i*2+1] = d[i];
    }
    vector<pair<int,int>> v;
    v.push_back({d.front(), 0});
    v.push_back({d.back(), sz(d)});
    for (int i = 0; i+1 < sz(d); i++) {
      v.push_back({max(d[i], d[i+1]), i+1});
    }
    sort(all(v));
    vector<int> u;
    for (int i = X; i < N; i++) {
      u.push_back(a[i]);
    }
    if (sz(u) < sz(v)) return false;
    while (!v.empty()) {
      auto [x, idx] = v.back(); v.pop_back();
      int y = u.back(); u.pop_back();
      if (y <= x) return false;
      else {
        b[2*idx] = y;
      }
    }
    for (int i = 0; i < N; i++) {
      if (b[i] == -1) {
        b[i] = u.back(); u.pop_back();
      }
    }

    ans = b;
    return true;
  };

  int lo = 0, hi = N;
  while (lo + 1 < hi) {
    int mid = (lo+hi)/2;
    (check(mid) ? lo : hi) = mid;
  }

  cout << lo << '\n';
  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << '\n';
}
