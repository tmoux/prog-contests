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
  const int mx = 2000;
  bitset<mx> all;
  F0R(i, N) all[i] = 1;
  bitset<mx> A, B;
  cin >> A >> B;

  if (A == 0 && B == 0) {
    cout << 0 << '\n';
  }
  else if (A != 0 && B != 0) {
    vector<int> moves;
    auto add_move = [&](int k) {
      moves.push_back(-k);
      if (k < 0) A = (A ^ (A << (-k))) & all;
      else A = (A ^ (A >> k)) & all;
    };
    int i = -1, j = -1;
    for (int k = N-1; k >= 0; k--) {
      if (A[k]) {
        i = k;
        break;
      }
    }
    for (int k = 0; k < N; k++) {
      if (B[k]) {
        j = k;
        break;
      }
    }
    if (i < j) {
      add_move(i - j);
      i = j;
    }
    for (int k = j-1; k >= 0; k--) {
      if (A[k]) {
        // zero out
        add_move(i - k);
      }
    }


    int idx = -1;
    for (int k = 0; k < N; k++) {
      if (A[k]) {
        idx = k;
        break;
      }
    }
    if (idx > j) add_move(idx - j);
    for (int k = j+1; k < N; k++) {
      if (A[k] != B[k]) {
        add_move(j - k);
      }
    }
    // cout << A << '\n';
    // cout << B << endl;

    assert(A == B);
    cout << sz(moves) << '\n';
    for (auto k: moves) {
      cout << k << ' ';
    }
    cout << '\n';
  }
  else {
    cout << -1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
