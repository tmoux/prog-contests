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
  int A, B; cin >> A >> B;
  vector<vector<int>> ans(A+1, vector<int>(B+1, 0));

  vector<int> v(N);
  F0R(i, N) cin >> v[i];

  for (int s = 0; s <= A + B; s++) {
    int minA = max(0, s - B);
    int maxA = min(A, s);

    int L = minA, R = maxA;
    int l = minA, r = maxA;

    for (auto x: v) {
      if (x > 0) {
        // decrease
        l -= x, r -= x;
        if (r <= minA) {
          L = R = minA;
          l = r = minA;
        }
        else {
          int excess = max(0, minA - l);
          ckmax(l, minA);
          L += excess;
        }
      }
      else {
        x = abs(x);
        // increase
        l += x, r += x;
        if (l >= maxA) {
          L = R = maxA;
          l = r = maxA;
        }
        else {
          int excess = max(0, r - maxA);
          ckmin(r, maxA);
          R -= excess;
        }
      }
    }

    for (int i = minA; i <= L; i++) {
      ans[i][s-i] = l;
    }
    for (int i = L + 1; i < R; i++) {
      ans[i][s-i] = l + (i - L);
    }
    for (int i = R; i <= maxA; i++) {
      ans[i][s-i] = r;
    }
  }

  F0R(i, A+1) {
    F0R(j, B+1) {
      cout << ans[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  solve();
}
