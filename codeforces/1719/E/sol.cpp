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

const int maxn = 51;
ll fib[maxn], fsum[maxn];

void init() {
  fib[0] = 0, fib[1] = 1;
  ll sum = 1;
  fsum[1] = 1;
  FOR(i, 2, maxn) {
    fib[i] = fib[i-1] + fib[i-2];
    sum += fib[i];
    fsum[i] = sum;
    // cout << fib[i] << ' ' << sum << ' ' << (double)fib[i] / sum << endl;
  }
}

bool found = false;

void search(vector<ll> v, int last, int n) {
  if (n == 0) {
    found = true;
    return;
  }

  vector<int> s;
  F0R(i, sz(v)) if (v[i] >= fib[n] && i != last) {
    s.push_back(i);
  }
  assert(sz(s) <= 2);
  if (s.empty()) return;
  for (int i: s) {
    v[i] -= fib[n];
    search(v, i, n-1); if (found) return;
    v[i] += fib[n];
  }
}

bool solve() {
  int K; cin >> K;
  vector<ll> V(K);
  ll sum = 0;
  F0R(i, K) {
    cin >> V[i];
    sum += V[i];
  }
  int n = -1;
  for (int i = 1; i <= 50; i++) {
    if (sum == fsum[i]) n = i;
  }
  if (n != -1) {
    sort(all(V));
    found = false;
    search(V, -1, n);
    return found;
  }
  else {
    return false;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init();
  int t; cin >> t;
  while (t--) cout << (solve() ? "YES" : "NO") << '\n';
}
