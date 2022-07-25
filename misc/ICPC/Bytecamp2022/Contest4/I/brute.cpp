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

const int maxn = 2e5+5;
int N, Q, P;

vector<int> adj_a[maxn];
vector<int> adj_b[maxn];

int par_a[maxn], depth_a[maxn];
void dfs_a(int i, int p) {
  par_a[i] = p;
  depth_a[i] = depth_a[p] + 1;
  for (int j: adj_a[i]) if (j != p) {
    dfs_a(j, i);
  }
}

int par_b[maxn], depth_b[maxn];
void dfs_b(int i, int p) {
  par_b[i] = p;
  depth_b[i] = depth_b[p] + 1;
  for (int j: adj_b[i]) if (j != p) {
    dfs_b(j, i);
  }
}

int query(int A, int B, int C, int D) {
  bitset<maxn> ba, bb;
  if (depth_a[A] > depth_a[B]) swap(A, B);
  while (depth_a[B] > depth_a[A]) {
    ba[B] = 1;
    B = par_a[B];
  }
  while (true) {
    ba[A] = 1;
    ba[B] = 1;
    if (A == B) break;
    else {
      A = par_a[A];
      B = par_a[B];
    }
  }

  if (depth_b[C] > depth_b[D]) swap(C, D);
  while (depth_b[D] > depth_b[C]) {
    bb[D] = 1;
    D = par_b[D];
  }
  while (true) {
    bb[C] = 1;
    bb[D] = 1;
    if (C == D) break;
    else {
      C = par_b[C];
      D = par_b[D];
    }
  }

  return (ba & bb).count();
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q >> P;
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj_a[a].push_back(b);
    adj_a[b].push_back(a);
  }
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj_b[a].push_back(b);
    adj_b[b].push_back(a);
  }

  dfs_a(1, 1);
  dfs_b(1, 1);

  int ans = 0;
  REP(Q) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    int A = (a + ans * P - 1) % N + 1;
    int B = (b + ans * P - 1) % N + 1;
    int C = (c + ans * P - 1) % N + 1;
    int D = (d + ans * P - 1) % N + 1;

    ans = query(A, B, C, D);
    cout << ans << '\n';
  }
}
