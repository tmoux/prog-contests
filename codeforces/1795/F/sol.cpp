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
  vector<vector<int>> adj(N);
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int K; cin >> K;
  vector<bool> start(N);
  vector<int> starts(K);
  F0R(i, K) {
    int ai; cin >> ai; ai--;
    starts[i] = ai;
    start[ai] = true;
  }

  auto check = [&](int l) -> bool {
    vector<int> need(N);
    F0R(i, K) {
      need[starts[i]] = l / K + (i < (l % K)) + 1;
    }

    vector<int> degree(N);
    F0R(i, N) degree[i] = sz(adj[i]);
    queue<int> q;
    F0R(i, N) {
      if (degree[i] == 1) {
        q.push(i);
      }
    }

    vector<array<int, 2>> data(N);
    vector<bool> vis(N, false);

    int close = 0;
    while (!q.empty()) {
      int i = q.front(); q.pop();
      if (vis[i]) continue;
      // DEBUG(i+1);
      vis[i] = true;
      if (start[i]) {
        for (int j: adj[i]) {
          if (vis[j] && data[j][1] > 0) return false;
        }
        int longest = 1;
        for (int j: adj[i]) {
          if (vis[j]) ckmax(longest, data[j][0] + 1);
        }
        if (longest >= need[i]) {
          data[i] = {0, 0};
          close++;
        }
        else {
          data[i] = {0, need[i] - 1};
        }
      }
      else {
        // continue longest path if needed
        bool taken = false;
        for (int j: adj[i]) {
          if (vis[j] && data[j][1] > 0) {
            if (taken) return false;
            else {
              taken = true;
              data[i] = {0, data[j][1] - 1};
              if (data[i][1] == 0) close++;
            }
          }
        }
        if (!taken) {
          int longest = 1;
          for (int j: adj[i]) {
            if (vis[j]) ckmax(longest, data[j][0] + 1);
          }
          data[i] = {longest, 0};
        }
        else if (data[i][1] > 0) {
          int longest = 0;
          for (int j: adj[i]) {
            if (vis[j]) ckmax(longest, data[j][0]);
          }
          if (longest >= data[i][1]) {
            data[i] = {0, 0};
            close++;
          }
        }
      }

      for (int j: adj[i]) {
        if (--degree[j] <= 1) {
          q.push(j);
        }
      }
    }
    assert(close <= K);
    return close == K;
  };

  int lo = 0, hi = N;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    // DEBUG(mid);
    (check(mid) ? lo : hi) = mid;
  }
  return lo;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
