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
  int N; cin >> N;
  int nonzero = 0;
  vector<int> A(N);
  vector<int> indices;
  F0R(i, N) {
    cin >> A[i];
    if (A[i] != 0) {
      nonzero++;
      indices.push_back(i);
    }
  }

  if (nonzero % 2 == 1) {
    cout << -1 << '\n';
  }
  else {
    vector<array<int, 2>> ans;
    if (indices.empty()) {
      cout << 1 << '\n';
      cout << 1 << ' ' << N << '\n';
      return;
    }
    if (!indices.empty() && indices[0] > 0) {
      ans.push_back({0, indices[0] - 1});
    }
    for (int i = 0; i < nonzero; i += 2) {
      if (i > 0) {
        for (int j = indices[i-1] + 1; j < indices[i]; j++) {
          ans.push_back({j, j});
        }
      }
      int x = A[indices[i]];
      int y = A[indices[i+1]];

      if (x != y) {
        for (int j = indices[i]; j <= indices[i+1]; j++) {
          ans.push_back({j, j});
        }
      }
      else {
        int j = indices[i+1] - 1;
        if (j == indices[i]) {
          ans.push_back({indices[i], indices[i+1]});
        }
        else {
          ans.push_back({indices[i], j-1});
          ans.push_back({j, indices[i+1]});
        }
      }
    }
    if (!indices.empty() && indices.back() < N-1) {
      ans.push_back({indices.back() + 1, N-1});
    }

    cout << sz(ans) << '\n';
    for (auto [l, r]: ans) {
      cout << l+1 << ' ' << r+1 << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
