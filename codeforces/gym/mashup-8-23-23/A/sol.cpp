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
const int BLK = 50;

set<int> adj[maxn];
vector<array<int, 3>> updates[maxn];

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
  map<pair<int, int>, vector<int>> ts;
  vector<int> cnt(N);
  FOR(t, 1, U+1) {
    int a, b; cin >> a >> b;
    a = toId[a], b = toId[b];
    if (a > b) swap(a, b);
    ts[{a, b}].push_back(t);

    if (adj[a].count(b)) {
      adj[a].erase(b);
      adj[b].erase(a);
    }
    else {
      adj[a].insert(b);
      adj[b].insert(a);
    }

    if (++cnt[a] % BLK == 0) {
      for (auto j: adj[a]) heights[a][t].push_back(j);
    }
    if (++cnt[b] % BLK == 0) {
      for (auto j: adj[b]) heights[b][t].push_back(j);
    }
  }
  for (const auto& [p, v]: ts) {
    auto [a, b] = p;
    for (int i = 0; i < sz(v); i += 2) {
      int t1 = v[i];
      int t2 = i + 1 < sz(v) ? v[i+1] : INF;
      updates[a].push_back({t1, b, t2});
      updates[b].push_back({t1, a, t2});
    }
  }
  F0R(i, N) sort(all(updates[i]));

  REP(Q) {
    int x, y, v; cin >> x >> y >> v;
    x = toId[x], y = toId[y];
    int t1 = mostRecent(x, v);
    int t2 = mostRecent(y, v);

    vector<int> a = heights[x][t1];
    array<int, 3> xx = {t1, INF, INF};
    for (auto it = upper_bound(all(updates[x]), xx); it != updates[x].end() && (*it)[0] <= v; ++it) {
      auto [_, j, t] = *it;
      if (v < t) a.push_back(j);
    }
    vector<int> b = heights[y][t2];
    array<int, 3> yy = {t2, INF, INF};
    for (auto it = upper_bound(all(updates[y]), yy); it != updates[y].end() && (*it)[0] <= v; ++it) {
      auto [_, j, t] = *it;
      if (v < t) b.push_back(j);
    }
    // DEBUG(t1);
    // DEBUG(t2);
    // cout << "HUH " << endl;
    // for (auto [t, v]: heights[y]) {
    //   cout << t << ' ' << v << endl;
    // }
    sort(all(a));
    sort(all(b));
    // cout << a << ' ' << b << endl;

    cout << minDist(a, b) << endl;
  }
}
