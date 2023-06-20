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

int msb(int x) {
  int r = -1;
  while (x > 0) {
    r++;
    x /= 2;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<int> v = {0};
  F0R(i, N) {
    int x; cin >> x;
    if (x == 0) continue;
    else v.push_back(x);
  }
  N = sz(v)-1;
  if (N == 0) {
    cout << 0 << '\n';
    return 0;
  }
  const int INF = 2e9;
  vector<array<int, 2>> dp(N+1, {INF, INF});
  dp[0][0] = dp[0][1] = 0;

  vector<int> R(N+1, N+1);
  vector<vector<int>> removes(N+2);
  vector<int> nxt(30, N+1), cnt(30, 0);
  for (int i = N; i >= 2; i--) {
    int r = msb(v[i]);
    int j = nxt[r];
    if (j <= N) {
      if (cnt[r] == 0) {
        ckmin(R[i], R[j]);
      }
      else ckmin(R[i], j);
    }
    F0R(k, 30) {
      if (k == r) continue;
      if (nxt[k] <= N) ckmin(R[i], R[nxt[k]]);
    }

    nxt[r] = i;
    cnt[r] = 0;
    F0R(k, 30) {
      if (v[i] & (1 << k)) {
        cnt[k] ^= 1;
      }
    }
  }

  {
    vector<int> cur(30, 0);
    int j = 1;
    for (int k = j; k <= N; k++) {
      int rr = msb(v[k]);
      if (cur[rr] != 1) {
        cur[rr] = 1;
        for (int l = 0; l < rr; l++) {
          if (cur[l] != -1 && (v[k] & (1 << l))) {
            cur[l] ^= 1;
          }
        }
      }
      else {
        R[j] = k;
        break;
      }
    }
  }
  FOR(i, 1, N+1) {
    removes[R[i]].push_back(i);
  }

  using P = pair<int, int>;
  priority_queue<P, vector<P>, greater<P>> pq;
  for (int i = 1; i <= N; i++) {
    ckmin(dp[i][1], min(dp[i-1][0], dp[i-1][1]) + 1);

    pq.push({dp[i-1][1], i});
    while (R[pq.top().second] <= i) pq.pop();
    ckmin(dp[i][0], pq.top().first);
  }

  cout << min(dp[N][0], dp[N][1]) << '\n';
}
