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

const int maxk = 30;
struct Trie {
  int dp[2][2];  
  Trie* nxt[2];
  Trie() {
    memset(dp, 0, sizeof dp);
    nxt[0] = nxt[1] = nullptr;
  }
};

void insert(Trie* cur, int i, int ai, int v) {
  for (int k = maxk-1; k >= 0; k--) {
    int i_k = (i >> k) & 1;
    int ai_k = (ai >> k) & 1;
    ckmax(cur->dp[i_k][ai_k], v);

    int c = ((i ^ ai) >> k) & 1;
    if (!cur->nxt[c]) cur->nxt[c] = new Trie();
    cur = cur->nxt[c];
  }
}

int query(Trie* cur, int i, int ai) {
  int ans = 0;
  for (int k = maxk-1; k >= 0; k--) {
    int i_k = (i >> k) & 1;
    int ai_k = (ai >> k) & 1;
    ckmax(ans, cur->dp[ai_k^1][i_k]);

    int c = ((i ^ ai) >> k) & 1;
    if (!cur->nxt[c]) break;
    else cur = cur->nxt[c];
  }
  return ans;
}

int solve() {
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  vector<int> dp(N);

  Trie* root = new Trie();
  int ans = 0;
  for (int i = 0; i < N; i++) {
    int tr = query(root, i, A[i]) + 1;
    ckmax(ans, tr);
    insert(root, i, A[i], tr);
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
