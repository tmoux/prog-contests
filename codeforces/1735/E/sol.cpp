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

using vi = vector<int>;

std::optional<tuple<int, int, vi>> solve() {
  int N; cin >> N;
  vector<int> A(N), B(N);
  F0R(i, N) {
    cin >> A[i];
  }
  F0R(i, N) {
    cin >> B[i];
  }

  auto check = [&](int dist) -> std::optional<tuple<int, int, vi>> {
    vector<array<int, 3>> as;
    vector<int> X;
    map<int, vector<int>> mpA, mpB;
    F0R(i, N) {
      mpA[A[i]].push_back(i);
      as.push_back({A[i], 0, i});
    }
    F0R(i, N) {
      mpB[B[i]].push_back(i);
      as.push_back({B[i], 1, i});
    }
    sort(all(as));
    vector<vector<bool>> used(2, vector<bool>(N, false));
    auto chk = [&](int t, vector<int>& v) {
      while (!v.empty() && used[t][v.back()]) v.pop_back();
    };
    auto upd = [&](int t, int i) {
      assert (!used[t][i]);
      used[t][i] = true;
    };
    while (!as.empty()) {
      auto [x, t, i] = as.back(); as.pop_back();
      if (used[t][i]) continue;
      else if (x > dist) {
        if (t == 0) {
          chk(1, mpB[x - dist]);
          if (mpB[x - dist].empty()) return std::nullopt;
          else {
            X.push_back(x);
            upd(t, i);
            int j = mpB[x - dist].back(); mpB[x - dist].pop_back();
            upd(1, j);
          }
        }
        else {
          chk(0, mpA[x - dist]);
          if (mpA[x - dist].empty()) return std::nullopt;
          else {
            X.push_back(dist - x);
            upd(t, i);
            int j = mpA[x - dist].back(); mpA[x - dist].pop_back();
            upd(0, j);
          }
        }
      }
      else {
        if (t == 0) {
          chk(1, mpB[dist - x]);
          if (mpB[dist - x].empty()) return std::nullopt;
          else {
            X.push_back(x);
            upd(t, i);
            int j = mpB[dist - x].back(); mpB[dist - x].pop_back();
            upd(1, j);
          }
        }
        else {
          chk(0, mpA[dist - x]);
          if (mpA[dist - x].empty()) return std::nullopt;
          else {
            X.push_back(dist - x);
            upd(t, i);
            int j = mpA[dist - x].back(); mpA[dist - x].pop_back();
            upd(0, j);
          }
        }
      }
    }
    int min_x = min(0, *min_element(all(X)));
    F0R(j, N) X[j] -= min_x;
    int p1 = 0 - min_x, p2 = dist - min_x;
    if (max({*max_element(all(X)), p1, p2}) <= 2000000000) {
      return std::optional<tuple<int, int, vi>>{{p1, p2, X}};
    }
    else return std::nullopt;
  };
  F0R(i, N) {
    auto c = check(A[0] + B[i]);
    if (c) return c;
    c = check(abs(A[0] - B[i]));
    if (c) return c;
  }

  return std::nullopt;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    auto c = solve();
    if (c) {
      cout << "YES" << '\n';
      auto [p1, p2, v] = *c;
      for (auto x: v) {
        cout << x << ' ';
      }
      cout << '\n';
      cout << p1 << ' ' << p2 << '\n';
    }
    else {
      cout << "NO" << '\n';
    }
  }
}
