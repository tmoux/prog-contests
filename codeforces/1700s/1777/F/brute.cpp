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

struct Node {
  Node *ch[2];
  Node() {
    ch[0] = ch[1] = nullptr;
  }
};

void insert(Node *root, int x) {
  F0Rd(i, 30) {
    int c = (x >> i) & 1;
    if (!root->ch[c]) root->ch[c] = new Node();
    root = root->ch[c];
  }
}

int get_max_xor(Node* root, int x) {
  int res = 0;
  F0Rd(i, 30) {
    int c = (x >> i) & 1;
    if (root->ch[c^1]) {
      res |= 1 << i;
      root = root->ch[c^1];
    }
    else root = root->ch[c];
  }
  return res;
}

int solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (auto& x: A) cin >> x;

  int ans = 0;
  F0R(i, N) {
    FOR(j, i, N) {
      int mx = 0;
      int xo = 0;
      FOR(k, i, j+1) {
        ckmax(mx, A[k]);
        xo ^= A[k];
      }
      ckmax(ans, mx ^ xo);
      // cout << i << ' ' << j << ": " << (mx ^ xo) << endl;
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
