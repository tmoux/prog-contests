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

const int maxn = 1e6+6;
int N, M, K, L, H;

struct Tracker {
  bitset<maxn> mask; // 0 if bad, 1 if allowed
  map<int, int> cnt;

  Tracker() {
    for (int i = 1; i <= N; i++) mask[i] = 1;
  }

  void add(int x) {
    if (++cnt[x] == 1) mask[x] = 0;
  }
  
  void remove(int x) {
    if (--cnt[x] == 0) mask[x] = 1;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> K >> L >> H;
  vector<int> queries;
  F0R(i, K) {
    int x; cin >> x;
    queries.push_back(x);
  }

  vector<array<int, 2>> bullets;
  F0R(i, L) {
    int x, y; cin >> x >> y;
    if (y > H + M) continue;
    bullets.push_back({y, x});
  }
  sort(all(bullets));
  bullets.erase(unique(all(bullets)), bullets.end());
  reverse(all(bullets));

  map<int, vector<int>> adds, removes;
  for (auto [y, x]: bullets) {
    adds[min(y+H-1, M+H)].push_back(x);
    removes[y].push_back(x);
  }

  bitset<maxn> dp;
  for (int i = 1; i <= N; i++) {
    dp[i] = 1;
  }
  Tracker tracker;

  for (int y = H+M; y >= H; y--) {
    for (auto x: adds[y]) {
      tracker.add(x);
    }

    /*
    for (int i = 1; i <= N; i++) {
      cout << tracker.mask[i];
    }
    cout << '\n';
    */


    dp = (((dp & tracker.mask) >> 1) | 
           (dp & tracker.mask) |
          ((dp & tracker.mask) << 1)) & tracker.mask;
    
    for (auto x: removes[y]) {
      tracker.remove(x);
    }

    /*
    DEBUG(y);
    for (int i = 1; i <= N; i++) {
      cout << dp[i] << ' ';
    }
    cout << '\n';
    */
  }

  int ans = 0;
  for (auto x: queries) {
    if (dp[x]) ans++;
  }

  cout << ans << '\n';
}
