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
  int N, M; cin >> N >> M;
  vector<vector<int>> adj(N);
  REP(M) {
    int a, b; cin >> a >> b;
    a--; b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<int> cnt(N);
  int F; cin >> F;
  vector<int> H(F);
  F0R(i, F) {
    cin >> H[i];
    H[i]--;
    cnt[H[i]]++;
  }
  int K; cin >> K;
  vector<int> P(K);
  F0R(i, K) {
    cin >> P[i]; P[i]--;
    P[i] = H[P[i]];
    cnt[P[i]]--;
  }

  const int MK = 1<<6;

  auto update_mask = [&](bitset<MK>& v, int j) {
    for (int i = 0; i < MK; i++) {
      if (v[i]) {
        v[i|(1<<j)] = 1;
      }
    }
  };

  vector<bitset<MK>> masks(N);
  vector<int> dist(N, 2e9);
  dist[0] = 0;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int i = q.front(); q.pop();

    masks[i][0] = 1;
    for (int j = 0; j < K; j++) {
      if (i == P[j]) {
        update_mask(masks[i], j);
      }
    }

    for (int j: adj[i]) if (dist[j] > dist[i] + 1) {
      dist[j] = dist[i] + 1;
      q.push(j);
    }

    for (int j: adj[i]) if (dist[j] == dist[i] + 1) {
      masks[j] |= masks[i];
    }
  }

  vector<bool> dp(MK, false);  
  dp[0] = true;
  F0R(i, N) {
    REP(cnt[i]) {
      F0Rd(x, MK) if (dp[x]) {
        F0R(y, MK) if (masks[i][y]) {
          dp[x|y] = true;
        }
      }
    }
  }

  int ans = 0;
  F0R(mask, MK) if (dp[mask]) {
    ckmax(ans, __builtin_popcount(mask));
  }
  return K - ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
