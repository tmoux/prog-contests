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

struct Tracker { // {{{
  int M;
  int cur;
  vector<int> cnt, mp;

  Tracker(int _m, vector<int> v) {
    M = _m;
    cur = M + 1;
    cnt.resize(M+2);
    mp.resize(M+1);
    for (auto x: v) {
      mp[x] = M + 1;
      cnt[M+1]++;
    }
  }

  void update(int i, int x) {
    cnt[mp[i]]--;
    mp[i] = x;
    cnt[mp[i]]++;
    while (cnt[cur] == 0) cur--;
  }

  int get_max() const {
    return cur;
  }
}; // }}}

int solve() {
  int N, M; cin >> N >> M;
  vector<bool> S(M+1, false);
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
    S[A[i]] = true;
  }
  sort(all(A)); A.erase(unique(all(A)), A.end());

  int ans = 2e9;
  vector<int> dp(M+1, 2e9);
  Tracker tracker(M, A);
  for (int i = M; i >= 1; i--) {
    ckmin(dp[i], i);
    if (S[i]) tracker.update(i, dp[i]);
    for (int j = i; j <= M; j += i) {
      if (j/i >= i) {
        ckmin(dp[j], max(dp[j/i], i));
        if (S[j]) tracker.update(j, dp[j]);
      }
    }

    int mx = tracker.get_max();
    if (i <= mx && mx <= M) {
      ckmin(ans, mx-i);
    }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
