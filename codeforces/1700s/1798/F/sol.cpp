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

const int maxn = 205;
int N, K;
vector<int> A;

int dp[maxn][maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  F0R(i, N) {
    int x; cin >> x;
    A.push_back(x);
  }
  vector<pair<int, int>> classes(K);
  F0R(i, K) {
    int s; cin >> s;
    classes[i] = {s, i};
  }
  sort(all(classes));

  vector<vector<int>> ans(K);
  int item;
  F0R(idx, sz(classes)) {
    auto [s, id] = classes[idx];
    if (idx + 1 < sz(classes)) {
      vector dp(2*s, vector(s+2, vector(s, -1)));
      dp[0][0][0] = 0;
      assert(sz(A) >= 2*s-1);
      F0R(i, 2*s-1) {
        F0R(j, s+1) {
          F0R(sum, s) {
            if (dp[i][j][sum] != -1) {
              dp[i+1][j][sum] = 0;
              dp[i+1][j+1][(sum+A[i])%s] = 1;
            }
          }
        }
      }
      assert(dp[2*s-1][s][0] != -1);
      int cj = s, csum = 0;
      vector<int> remove(sz(A));
      for (int i = 2*s-1; i > 0; i--) {
        assert(dp[i][cj][csum] != -1);
        if (dp[i][cj][csum] == 1) {
          cj--;
          csum = (csum + s - (A[i-1] % s)) % s;
          remove[i-1] = 1;
        }
      }
      assert(cj == 0 && csum == 0);
      vector<int> nA;
      F0R(i, sz(A)) {
        if (!remove[i]) {
          nA.push_back(A[i]);
        }
        else {
          ans[id].push_back(A[i]);
        }
      }
      A = nA;
    }
    else {
      int total = 0;
      assert(sz(A) == s-1);
      for (auto x: A) {
        ans[id].push_back(x);
        total = (total + x) % s;
      }
      item = (s - total) + s;
      ans[id].push_back(item);
    }
  }

  cout << item << '\n';
  F0R(i, K) {
    assert(accumulate(all(ans[i]), 0) % sz(ans[i]) == 0);
    for (auto x: ans[i]) {
      cout << x << ' ';
    }
    cout << '\n';
  }
}
