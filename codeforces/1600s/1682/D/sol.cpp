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
  int n; cin >> n;
  string s; cin >> s;
  int ones = count(all(s), '1');
  if (ones == 0 || ones % 2 == 1) {
    cout << "NO\n";
  }
  else {
    vector<pair<int,int>> ans;
    auto add_edge = [&](int a, int b) {
      ans.push_back({a, b});
    };
    auto find_next = [&](int i) {
      for (int j = i+1; j < n; j++) {
        if (s[j] == '1') return j;
      }
      assert(false);
    };

    int start = find_next(-1);
    rotate(s.begin(), s.begin() + start, s.end());

    int last = n-1;
    while (s[last] == '0') last--;

    if (ones == 2) {
      int b = find_next(0);
      for (int i = 0; i+1 < b; i++) {
        add_edge(i, i+1);
      }
      add_edge(b-1, n-1);
      for (int i = b; i+1 <= n-1; i++) {
        add_edge(i, i+1);
      }
    }
    else {
      int b = find_next(0);
      for (int i = 0; i+1 <= b; i++) {
        add_edge(i, i+1);
      }
      auto rec = y_combinator([&](auto rec, int a) -> void {
        int b = find_next(a); 
        int c = find_next(b);
        for (int i = a; i+1 <= b; i++) {
          add_edge(i, i+1);
        }
        if (c != last || c == n-1) {
          add_edge(a, b+1);
          for (int i = b+1; i+1 <= c; i++) {
            add_edge(i, i+1);
          }
        }
        else if (b == c-1) {
          add_edge(a, n-1);
          for (int i = c; i+1 <= n-1; i++) {
            add_edge(i, i+1);
          }
        }
        else {
          add_edge(a, b+1);
          for (int i = b+1; i+1 < c; i++) {
            add_edge(i, i+1);
          }
          add_edge(c-1, n-1);
          for (int i = c; i+1 <= n-1; i++) {
            add_edge(i, i+1);
          }
        }

        if (c != last) {
          rec(c);
        }
      });
      rec(b);
    }

    assert(sz(ans) == n-1);
    cout << "YES\n";
    for (auto [u, v]: ans) {
      int uu = (u + start) % n + 1;
      int vv = (v + start) % n + 1;
      cout << uu << ' ' << vv << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

