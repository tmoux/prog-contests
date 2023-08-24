#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const int maxn = 2e5+5;
int N, D, U, Q;
int H[maxn];
const int BLK = 15;

set<int> adj[maxn];
vector<pair<int, int>> updates[maxn];

map<int, vector<int>> heights[maxn];

const int INF = 1e9;
int minDist(const vector<int>& a, const vector<int>& b) {
  int ans = INF;
  int j = 0;
  for (int x: a) {
    while (j < sz(b) && b[j] < x) j++;
    if (j-1 >= 0) ckmin(ans, abs(H[x] - H[b[j-1]]));
    if (j < sz(b)) ckmin(ans, abs(H[x] - H[b[j]]));
  }
  return ans;
}

int mostRecent(int i, int t) {
  auto it = heights[i].upper_bound(t);
  if (it == heights[i].begin()) return 0;
  else return prev(it)->first;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> D >> U >> Q;
  vector<pair<int, int>> v;
  F0R(i, N) {
    cin >> H[i];
    v.emplace_back(H[i], i);
  }
  sort(all(v));
  vector<int> toId(N);
  F0R(i, N) {
    toId[v[i].second] = i;
    H[i] = v[i].first;
  }
  FOR(t, 1, U+1) {
    int a, b; cin >> a >> b;
    a = toId[a], b = toId[b];
    updates[a].emplace_back(t, b);
    updates[b].emplace_back(t, a);

    if (adj[a].count(b)) {
      adj[a].erase(b);
      adj[b].erase(a);
    }
    else {
      adj[a].insert(b);
      adj[b].insert(a);
    }

    if (sz(updates[a]) % BLK == 0) {
      for (auto j: adj[a]) heights[a][t].push_back(j);
    }
    if (sz(updates[b]) % BLK == 0) {
      for (auto j: adj[b]) heights[b][t].push_back(j);
    }
  }

  REP(Q) {
    int x, y, v; cin >> x >> y >> v;
    x = toId[x], y = toId[y];
    int t1 = mostRecent(x, v);
    int t2 = mostRecent(y, v);

    set<int> sa(all(heights[x][t1]));
    for (auto it = upper_bound(all(updates[x]), make_pair(t1, INF)); it != updates[x].end() && it->first <= v; ++it) {
      int j = it->second;
      if (sa.count(j)) sa.erase(j);
      else sa.insert(j);
    }
    set<int> sb(all(heights[y][t2]));
    for (auto it = upper_bound(all(updates[y]), make_pair(t2, INF)); it != updates[y].end() && it->first <= v; ++it) {
      int j = it->second;
      if (sb.count(j)) sb.erase(j);
      else sb.insert(j);
    }

    vector<int> a(all(sa)), b(all(sb));
    cout << a << ' ' << b << endl;
    cout << minDist(a, b) << endl;
  }
}
