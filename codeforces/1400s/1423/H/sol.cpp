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

//implement DSU with rollbacks
//when rolling back change (a,b) (a is parent of b):
//a.szX -= b.szX, a.szY -= b.szY
//Reset b to be the parent of itself
const int maxn = 5e5+5;
int N, Q;

struct Node //node in segment tree of queries
{
  int se, en;
  vector<pair<int,int>> edges;
  //edges that are present in this node
} nodes[4*maxn+5];

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
//DSU information
int parent[2*maxn+10];
int sz[2*maxn+10];

int findParent(int i) {
  if (parent[i] == i) return i;
  return findParent(parent[i]);
}

void merge(int a, int b) {
  a = findParent(a);
  b = findParent(b);
  if (a == b) return;
  if (sz[a] < sz[b]) swap(a,b);
  parent[b] = a;
  sz[a] += sz[b];
  active.push(b);
}

void rollback() {
  int b = active.top(); active.pop();
  int a = parent[b];
  parent[b] = b;
  sz[a] -= sz[b];
}

int queries[maxn];
vector<pair<int, int>> ans;

void DFS(int i) {
  int t0 = active.size();
  //add this interval's edges
  for (const auto& p: nodes[i].edges) {
    merge(p.first,p.second);
  }
  if (nodes[i].se == nodes[i].en) {
    int z = queries[nodes[i].se];
    if (z > 0) {
      ans.emplace_back(nodes[i].se, sz[findParent(z)]);
    }
  }
  else {
    DFS(i*2);
    DFS(i*2+1);
  }
  //at the end, rollback edges
  while ((int)active.size() > t0) {
    rollback();
  }
}

int timeId[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q;
  int K; cin >> K;
  build(1, 0, Q);
  int cur_t = 0;
  vector<array<int, 4>> qs;
  F0R(id, Q) {
    int t; cin >> t;
    if (t == 1) {
      int x, y; cin >> x >> y;
      qs.push_back({id, cur_t, x, y});
    }
    else if (t == 2) {
      int z; cin >> z;
      queries[id] = z;
    }
    else if (t == 3) {
      timeId[++cur_t] = id;
    }
  }
  timeId[++cur_t] = Q;
  for (auto [id, t, x, y]: qs) {
    addInterval(1, id, timeId[min(cur_t, t+K)], {x, y});
  }
  FOR(i, 1, N+1) parent[i] = i, sz[i] = 1;
  DFS(1);
  sort(all(ans));
  for (auto [id, x]: ans) {
    cout << x << '\n';
  }
}
