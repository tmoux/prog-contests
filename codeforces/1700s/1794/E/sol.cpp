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
int N, A[maxn];
vector<int> adj[maxn];

const int MOD = 1e9+7;

void madd(int& a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
}
int mult(int a, int b) {
  return (1LL * a * b) % MOD;
}
int modexp(int a, int b) {
  int r = 1;
  while (b) {
    if (b&1) r = mult(r, a);
    a = mult(a, a);
    b >>= 1;
  }
  return r;
}

const int K = 3;
int B[K];
void initHash() {
  std::uniform_int_distribution<> gen(2, 100); // ???
  F0R(i, K) {
    B[i] = gen(rng);
  }
}
using T = array<int, K>;
set<T> good_hashes;

T ones() {
  T a;
  F0R(i, K) a[i] = 1;
  return a;
}

T merge(T a, T b) {
  F0R(i, K) madd(a[i], b[i]);
  return a;
}

T diff(T a, T b) {
  F0R(i, K) madd(a[i], MOD-b[i]);
  return a;
}

T shift(T a) {
  F0R(i, K) a[i] = mult(a[i], B[i]);
  return a;
}

T sub_hash[maxn];
void dfs1(int i, int p) {
  sub_hash[i] = ones();
  for (int j: adj[i]) {
    if (j == p) continue;
    dfs1(j, i);
    T s = shift(sub_hash[j]);
    sub_hash[i] = merge(sub_hash[i], s);
  }
}

vector<int> ans;
void dfs2(int i, int p, T cur) {
  T c = merge(sub_hash[i], cur);
  if (good_hashes.count(c)) {
    ans.push_back(i);
  }
  for (int j: adj[i]) {
    if (j == p) continue;
    T ncur = shift(diff(c, shift(sub_hash[j])));
    dfs2(j, i, ncur);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  initHash();
  cin >> N;
  map<int, int> mp;
  F0R(i, N-1) {
    cin >> A[i];
    mp[A[i]]++;
  }
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  T total = {0};
  for (int i = 0; i < N; i++) {
    F0R(j, K) {
      madd(total[j], mult(modexp(B[j], i), mp[i]));
    }
  }
  F0R(i, N) {
    T ntotal = total;
    F0R(j, K) madd(ntotal[j], modexp(B[j], i));
    good_hashes.insert(ntotal);
  }

  dfs1(1, 1);
  dfs2(1, 1, {0});

  sort(all(ans));
  cout << sz(ans) << '\n';
  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << '\n';
}
