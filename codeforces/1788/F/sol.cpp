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

const int maxn = 250005;
int N, Q;
vector<pair<int, int>> adj[maxn];
vector<pair<int, int>> g[maxn];

int ans[maxn];

int comps[maxn], color[maxn];
bool poss = true;

void dfs(int i, int c, int comp, int idx) {
  if (!poss) return;
  color[i] = c;
  comps[i] = comp;
  for (auto [j, x]: g[i]) {
    int y = (x >> idx) & 1;
    if (color[j] == -1) dfs(j, c^y, comp, idx);
    else if (color[j] != (c^y)) {
      poss = false;
      break;
    }
  }
}

int pfx[maxn];
array<int, 2> cnt[maxn];

void recon(int i, int p, int idx) {
  for (auto [j, id]: adj[i]) {
    if (j != p) {
      ans[id] |= (pfx[i] ^ pfx[j]) << idx;
      recon(j, i, idx);
    }
  }
}

bool solve_bit(int idx) {
  F0R(i, N) {
    color[i] = comps[i] = -1;
    cnt[i][0] = cnt[i][1] = 0;
  }
  int num_comps = 0;
  F0R(i, N) {
    if (color[i] == -1) {
      dfs(i, 0, num_comps, idx);
      num_comps++;
    }
  }
  if (!poss) return false;
  int csum = 0, comp_idx = -1;
  F0R(i, N) {
    if (sz(adj[i])&1) cnt[comps[i]][color[i]] ^= 1;
    pfx[i] = color[i];
    if ((sz(adj[i])&1) && color[i]) {
      csum ^= 1;
    }
  }
  FOR(c, 1, num_comps) {
    if (cnt[c][0] ^ cnt[c][1]) {
      comp_idx = c;
      break;
    }
  }

  if (comp_idx != -1 && csum == 1) {
    // If we can make the xor 0 by flipping a component, do so
    F0R(i, N) {
      if (comps[i] == comp_idx) {
        pfx[i] = color[i] ^ 1;
      }
    }
  }
  recon(0, 0, idx);
  return true;
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q;
  F0R(i, N-1) {
    int u, v; cin >> u >> v;
    u--, v--;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
  }
  F0R(i, Q) {
    int u, v, x; cin >> u >> v >> x;
    u--, v--;
    g[u].emplace_back(v, x);
    g[v].emplace_back(u, x);
  }

  bool poss = true;
  F0R(i, 30) {
    poss &= solve_bit(i);
    if (!poss) break;
  }

  if (poss) {
    cout << "Yes\n";
    F0R(i, N-1) {
      cout << ans[i] << " \n"[i == N-2];
    }
  }
  else {
    cout << "No\n";
  }
}
