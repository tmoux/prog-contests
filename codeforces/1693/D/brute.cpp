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

// Need a better equivalent condition for an array to be decinc.

const int maxn = 2e5+5;
int N, P[maxn];

bool check(int l, int r) {
  int n = r-l+1;
  F0R(mask, 1 << n) {
    vector<int> inc, dec;
    F0R(i, n) {
      (mask & (1 << i) ? inc : dec).push_back(P[i+l]);
    }
    bool p = true;
    FOR(i, 1, sz(inc)) if (inc[i] < inc[i-1]) p = false;
    FOR(i, 1, sz(dec)) if (dec[i] > dec[i-1]) p = false;
    if (p) return true;
  }
  return false;
}

bool check2(int l, int r) {
  FOR(i1, l, r+1) {
    FOR(i2, i1+1, r+1) {
      FOR(i3, i2+1, r+1) {
        FOR(i4, i3+1, r+1) {
          if (P[i1] > P[i2] && P[i4] > P[i1] && P[i3] > P[i4]) {
            return true;
          }
          if (P[i1] < P[i2] && P[i4] < P[i1] && P[i3] < P[i4]) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) cin >> P[i];
  int ans = 0;
  F0R(i, N) {
    FOR(j, i, N) {
      if (check(i, j)) ans++;
    }
  }
  cout << ans << '\n';
  return 0;
  vector<int> p(N); iota(all(p), 0);
  do {
    F0R(i, N) P[i] = p[i];
    bool b = check(0, N-1);
    cout << p << ": " << b << '\n';
    if (!b) {
      assert(check2(0, N-1));
    }
  } while (next_permutation(all(p)));
  //
  F0R(i, N) {
    cin >> P[i];
  }
}
