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

struct Rectangle {
  int r1, c1, r2, c2, id;
  bool operator<(const Rectangle& rhs) const {
    return c1 < rhs.c1;
  }
};

void solve() {
  int N; cin >> N;
  vector<Rectangle> vs;
  F0R(i, N) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    vs.push_back({r1, c1, r2, c2, i});
  }
  sort(all(vs));
  pair<int, int> cur1 = {0, -1}, cur2 = {0, -1}; // column, id
  vector<array<int, 4>> ans(N);

  for (auto [r1, c1, r2, c2, id]: vs) {
    if (r1 == r2) {
      if (r1 == 1) {
        if (cur1.first >= c2) {
          // useless, delete
          ans[id] = {0, 0, 0, 0};
        }
        else {
          // move to end
          ans[id] = {r1, max(c1, cur1.first + 1), r2, c2};
          cur1 = {c2, id};
        }
      }
      else {
        if (cur2.first >= c2) {
          // useless, delete
          ans[id] = {0, 0, 0, 0};
        }
        else {
          // move to end
          ans[id] = {r1, max(c1, cur2.first + 1), r2, c2};
          cur2 = {c2, id};
        }
      }
    }
    else {
      if (cur1.first >= c2 && cur2.first >= c2) {
        // useless, delete
        ans[id] = {0, 0, 0, 0};
      }
      else if (c2 > max(cur1.first, cur2.first)) {
        // overtake both
        if (cur1.second != -1) ckmin(ans[cur1.second][3], c1-1);
        if (cur2.second != -1) ckmin(ans[cur2.second][3], c1-1);
        ans[id] = {r1, c1, r2, c2};
        cur1 = {c2, id};
        cur2 = {c2, id};
      }
      else if (cur1.first >= c2 && cur2.first < c2) {
        // overtake cur2
        ans[id] = {2, max(c1, cur2.first+1), 2, c2};
        cur2 = {c2, id};
      }
      else if (cur1.first < c2 && cur2.first >= c2) {
        // overtake cur1
        ans[id] = {1, max(c1, cur1.first+1), 1, c2};
        cur1 = {c2, id};
      }
      else assert(false);
    }
  }

  const int MX = 1e9;
  int C[] = {MX, MX};
  F0Rd(i, N) {
    int id = vs[i].id;
    auto& [a, b, c, d] = ans[id];
    for (int r: {a, c}) {
      ckmin(d, C[r-1]);
    }
    for (int r: {a, c}) {
      ckmin(C[r-1], b-1);
    }
  }

  int area = 0;
  for (auto [a, b, c, d]: ans) {
    if (b <= d && a != 0) {
      area += (d - b + 1) * (c - a + 1);
    }
  }

  cout << area << '\n';
  F0R(i, N) {
    auto [a, b, c, d] = ans[i];
    if (b <= d && a != 0) {
      cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
    }
    else {
      cout << 0 << ' ' << 0 << ' ' << 0 << ' ' << 0 << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
