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
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  if (N == 3 && A[1] == 3) {
    cout << "NO\n";
    return;
  }

  auto solve_0 = [&](vector<int> A) {
    vector<int> v = {N-1, N-2};
    int cur = A[N-2];
    for (int i = N-3; i >= 0; i--) {
      if (A[i] < cur) {
        v.push_back(i);
        cur = A[i];
      }
    }
    reverse(all(v));
    // cout << v << endl;

    vector<array<int, 3>> ans;
    F0R(idx, sz(v)-1) {
      for (int i = idx == 0 ? 0 : v[idx-1]+1; i < v[idx]; i++) {
        ans.push_back({i, v[idx], v[idx+1]});
      }
    }
    return ans;
  };

  auto output = [&](vector<array<int, 3>> ans, vector<pair<int, int>> swaps) {
    cout << "YES\n";
    cout << (sz(ans) + sz(swaps)) << ' ' << sz(swaps) << '\n';
    for (auto [i, j]: swaps) {
      cout << 1 << ' ' << i+1 << ' ' << j+1 << '\n';
    }
    int del = 0;
    for (auto [a, b, c]: ans) {
      cout << 2 << ' ' << a+1-del << ' ' << b+1-del << ' ' << c+1-del << '\n';
      del++;
    }
  };
  // check if can do 0
  if (A[N-2] < A[N-1]) {
    auto ans = solve_0(A);
    output(ans, {});
    return;
  }

  // check if can do 1
  int pos = -1;
  F0R(i, N) if (A[i] == N) pos = i;
  if (pos != N-2) {
    // move to end and delete all
    swap(A[N-1], A[pos]);
    auto ans = solve_0(A);
    output(ans, {{N-1, pos}});
  }
  else {
    int j = -1;
    for (int i = N-4; i >= 0; i--) {
      if (A[i] < A[N-1]) {
        j = i;
        break;
      }
    }
    if (j != -1) {
      swap(A[j], A[pos]);
      auto ans = solve_0(A);
      output(ans, {{j, pos}});
    }
    else {
      // must do 2
      swap(A[pos], A[0]);
      swap(A[0], A[N-1]);
      auto ans = solve_0(A);
      output(ans, {{pos, 0}, {0, N-1}});
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
