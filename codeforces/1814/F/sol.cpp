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
int N, M, L[maxn], R[maxn];

struct Node // node in segment tree of queries
{
  int se, en;
  vector<pair<int,int>> edges;
  // edges that are present in this node
} nodes[4*maxn];

void build(int i, int se, int en) {
  nodes[i].se = se;
  nodes[i].en = en;
  if (se == en) return;
  int m = (se+en)>>1;
  build(i*2,se,m);
  build(i*2+1,m+1,en);
}

void addInterval(int i, int l, int r, const pair<int,int>& p) {
  if (l <= nodes[i].se && nodes[i].en <= r) {
    nodes[i].edges.push_back(p);
    return;
  }
  if (nodes[i].se == nodes[i].en) return;
  int mid = (nodes[i].se+nodes[i].en)/2;
  if (mid >= l) addInterval(i*2,l,r,p);
  if (mid < r) addInterval(i*2+1,l,r,p);
}

stack<int> active;
// DSU information
int parent[maxn];
int sz[maxn];
int cur_comp = 1;
vector<int> comp[maxn];

const int MAXM = 8e6;
vector<int> adj[MAXM];
bool touch[MAXM];

int newComp() {
  return cur_comp++;
}

int findParent(int i) {
  if (parent[i] == i) return i;
  return findParent(parent[i]);
}

void merge(int a, int b) {
  a = findParent(a);
  b = findParent(b);
  if (a == b) return;
  if (sz[a] < sz[b]) swap(a, b);
  parent[b] = a;
  sz[a] += sz[b];
  active.push(b);
  int nc = newComp();
  int na = comp[a].back(), nb = comp[b].back();
  adj[nc].push_back(na);
  adj[nc].push_back(nb);
  comp[a].push_back(nc);
}

void rollback() {
  int b = active.top(); active.pop();
  int a = parent[b];
  parent[b] = b;
  sz[a] -= sz[b];
  comp[a].pop_back();
}

void DFS(int i) {
  int t0 = active.size();
  // add this interval's edges
  for (const auto& p: nodes[i].edges) {
    merge(p.first,p.second);
  }
  if (nodes[i].se == nodes[i].en) {
    // at leaf
    int c = comp[findParent(1)].back();
    touch[c] = 1;
  }
  else {
    DFS(i*2);
    DFS(i*2+1);
  }
  // at the end, rollback edges
  while (sz(active) > t0) {
    rollback();
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  FOR(i, 1, N+1) {
    cin >> L[i] >> R[i];
    if (L[i] > R[i]) swap(L[i], R[i]);
  }
  build(1, 1, 200000);
  F0R(i, M) {
    int a, b; cin >> a >> b;

    int l = max(L[a], L[b]);
    int r = min(R[a], R[b]);
    if (l <= r) {
      addInterval(1, l, r, {a, b});
    }
  }
  // initialize DSU
  FOR(i, 1, N+1) {
    parent[i] = i;
    sz[i] = 1;
    comp[i].push_back(newComp());
  }

  DFS(1);

  // go in topological order (reverse)
  for (int i = cur_comp-1; i >= 1; i--) {
    for (int j: adj[i]) {
      touch[j] |= touch[i];
    }
  }

  FOR(i, 1, N+1) {
    if (touch[i]) {
      cout << i << ' ';
    }
  }
  cout << '\n';
}
