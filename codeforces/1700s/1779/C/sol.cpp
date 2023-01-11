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

int solve() {
  int N; cin >> N;
  int M; cin >> M; M--;
  vector<ll> A(N);
  vector<ll> pre(N);

  int ops = 0;
  F0R(i, N) {
    cin >> A[i];
    pre[i] = A[i] + (i == 0 ? 0 : pre[i-1]);
  }
  ll min_prefix = *min_element(all(pre));
  if (pre[M] == min_prefix) {
    return 0;
  }
  /*
  else if (A[M] > 0) {
    ll x = A[M];
    A[M] *= -1;
    ops++;
    for (int i = M; i < N; i++) {
      pre[i] -= 2 * x;
    }
  }
  */
  ll target = pre[M];
  // cout << pre << endl;
  // DEBUG(target);
  priority_queue<ll> pq;
  for (int i = M; i >= 0; i--) {
    if (A[i] > 0) pq.push(A[i]);
    while (pre[i] < target) {
      // cout << "idx " << i << endl;
      // DEBUG(target);
      // DEBUG(pre[i]);
      assert(!pq.empty());
      auto x = pq.top(); pq.pop();
      target -= 2 * x;
      ops++;
    }
  }
  // DEBUG(ops);

  // cout << pre << endl;
  priority_queue<ll> pq2;
  ll sum = target;
  for (int i = M+1; i < N; i++) {
    if (A[i] < 0) pq2.push(-A[i]);
    sum += A[i];
    while (sum < target) {
      assert(!pq2.empty());
      ll x = pq2.top(); pq2.pop();
      sum += 2 * x;
      ops++;
    }
  }

  return ops;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
