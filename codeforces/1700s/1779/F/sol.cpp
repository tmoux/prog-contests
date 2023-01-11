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

const int maxn = 2e5+5, maxx = 1<<5;
int N, A[maxn];
vector<int> adj[maxn];
int sub_size[maxn];

int tin[maxn], timer = 1;
vector<int> tout[maxn];
void dfs(int i) {
  tin[timer++] = i;
  sub_size[i] = 1;
  for (int j: adj[i]) {
    dfs(j);
    sub_size[i] += sub_size[j];
    A[i] ^= A[j];
  }
  tout[timer].push_back(i);
}

int prev_idx[maxn][maxx];
int cur[maxx];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  memset(prev_idx, -1, sizeof prev_idx);
  memset(cur, -1, sizeof cur);
  cin >> N;
  int target = 0;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    target ^= A[i];
  }
  for (int i = 2; i <= N; i++) {
    int p; cin >> p;
    adj[p].push_back(i);
  }
  // knock out N even first, or if target is 0
  if (N % 2 == 0 || target == 0) {
    cout << 2 << '\n';
    cout << 1 << ' ' << 1 << '\n';
    return 0;
  }
  dfs(1);

  int idx = -1;
  cur[0] = 0;
  for (int t = 1; t <= N; t++) {
    for (int j: tout[t]) {
      F0R(x, maxx) if (prev_idx[j][x] != -1) {
        cur[x] = j;
      }
    }
    int i = tin[t];
    if (sub_size[i] % 2 == 0) {
      F0R(x, maxx) {
        prev_idx[i][x^A[i]] = cur[x];
        if ((x^A[i]) == target && prev_idx[i][x^A[i]] != -1) {
          idx = i;
        }
      }
    }
  }

  if (idx == -1) {
    cout << -1 << '\n';
  }
  else {
    vector<int> ans;
    int t = target;
    while (idx != 0) {
      ans.push_back(idx);
      int new_idx = prev_idx[idx][t];
      t ^= A[idx];
      idx = new_idx;
    }
    ans.push_back(1);
    ans.push_back(1);

    cout << sz(ans) << '\n';
    F0R(i, sz(ans)) {
      cout << ans[i] << " \n"[i == sz(ans)-1];
    }
  }
}
