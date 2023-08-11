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

// If there's a gap of size > n/2, then impossible.
//

const int maxn = 5005;
int N, MOD;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> MOD;

  const int all = (1 << N) - 1;
  vector<vector<int>> adj(1 << N);
  vector<int> indegree(1 << N);
  F0R(mask, 1 << N) {
    F0R(i, N) {
      FOR(j, i+1, N) {
        if ((mask & (1 << i)) && (mask & (1 << j))) {
          int c = 0;
          for (int k = i; k <= j; k++) {
            if (mask & (1 << k)) {
              c++;
            }
          }
          if (c * 2 >= j-i+1) {
            int nmask = mask;
            for (int k = i; k <= j; k++) {
              nmask |= 1 << k;
            }
            if (nmask != mask) {
              adj[nmask].push_back(mask);
            }
          }
        }
      }
    }
  }

  F0R(i, 1 << N) {
    sort(all(adj[i])); adj[i].erase(unique(all(adj[i])), adj[i].end());
    for (auto j: adj[i]) indegree[j]++;
  }

  queue<int> q;
  q.push(all);

  vector<bool> v(1 << N);
  while (!q.empty()) {
    int i = q.front(); q.pop();
    v[i] = 1;
    for (int j: adj[i]) {
      if (!v[j]) {
        q.push(j);
      }
    }
  }

  int cnt = 0;
  F0R(i, 1 << N) {
    if (v[i] && (i & (1 << 0)) && (i & (1 << (N-1)))) {
      int gap = 0;
      int cur = 0;
      F0R(j, N) {
        if (i & (1 << j)) {
          cur = 0;
        }
        else {
          cur++;
          ckmax(gap, cur);
        }
      }
      // if (gap * 2 <= N) {
      // int mn = 0;
      // F0R(j, N) {
      //   int s = 0;
      //   FOR(k, j, N) {
      //     if (i & (1 << k)) s++;
      //     else s--;
      //     ckmin(mn, s);
      //   }
      // }
      cnt++;
      // if (true) {
      //   cout << bitset<N>(i) << endl;
      // }
    }
  }
  cout << (cnt % MOD) << '\n';
}
