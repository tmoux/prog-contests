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

const int maxn = 505;
int N, x;
int A[maxn];

int ans = 0;
bool simul() {
  vector<int> a(N);
  F0R(i, N) a[i] = A[i];
  while (true) {
    int cnt = 0;
    F0R(i, N) if (a[i] > 0) cnt++;
    F0R(i, N) {
      a[i] -= min(a[i], cnt-1);
    }

    int ncnt = 0;
    F0R(j, N) if (a[j] > 0) ncnt++;
    if (ncnt == 0) return false;
    else if (ncnt == 1) return true;
  }
}

void rec(int i) {
  if (i == N) {
    int mx = 0;
    F0R(j, N) {
      ckmax(mx, A[j]);
    }
    int cnt = 0;
    F0R(j, N) {
      if (A[j] == mx) cnt++;
    }
    if (cnt > 1) ans++;
    if (simul()) {
      F0R(j, N) {
        cout << A[j] << ' ';
      }
      cout << '\n';
    }
    // F0R(j, N) {
    //   cout << A[j] << ' ';
    // }
    // cout << endl;
    return;
  }

  for (int j = 1; j <= x; j++) {
    A[i] = j;
    rec(i+1);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> x;
  rec(0);
  // cout << ans << endl;
}
