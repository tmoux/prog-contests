#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

const int maxn = 5000;
int N, M;
int P[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> M >> N;
  F0R(i, N) cin >> P[i];
  vector<bitset<maxn>> bs(N);
  F0R(i, N) bs[i] = bitset<maxn>().set();

  bitset<maxn> lt = bitset<maxn>();
  F0R(i, M) {
    lt.reset();
    vector<pair<int, int>> vec;
    F0R(j, N) {
      int x; cin >> x;
      vec.push_back({x, j});
    }

    sort(all(vec));
    vec.push_back({1e9, -1});
    int x = 0;
    vector<int> v;
    for (auto [y, j]: vec) {
      if (y == x) {
        v.push_back(j);
      }
      else {
        for (int j: v) {
          bs[j] &= lt;
        }
        for (int j: v) {
          lt[j] = 1;
        }
        v = {j};
        x = y;
      }
    }
  }

  vector<int> indegree(N);
  F0R(i, N) {
    F0R(j, N) {
      if (bs[i][j]) {
        indegree[i]++;
      }
    }
  }
  queue<int> q;
  F0R(i, N) {
    if (!indegree[i]) {
      q.push(i);
    }
  }
  vector<ll> dp(N);
  F0R(i, N) dp[i] = P[i];
  while (!q.empty()) {
    int i = q.front(); q.pop();
    F0R(j, N) if (bs[j][i]) {
      ckmax(dp[j], dp[i] + P[j]);
      if (--indegree[j] == 0) {
        q.push(j);
      }
    }
  }

  cout << *max_element(all(dp)) << '\n';
}
