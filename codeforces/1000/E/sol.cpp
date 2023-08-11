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

int N, M;

using vi = vector<int>;
using pii = pair<int, int>;

namespace BC {
vi num, st;
vector<vector<pii>> ed;
vector<pii> edges;
vector<bool> isBridge;
int Time;
template<class F>
int dfs(int at, int par, F& f) {
  int me = num[at] = ++Time, e, y, top = me;
  for (auto pa : ed[at]) if (pa.second != par) {
      tie(y, e) = pa;
      if (num[y]) {
        top = min(top, num[y]);
        if (num[y] < me)
          st.push_back(e);
      } else {
        int si = sz(st);
        int up = dfs(y, e, f);
        top = min(top, up);
        if (up == me) {
          st.push_back(e);
          f(vi(st.begin() + si, st.end()));
          st.resize(si);
        }
        else if (up < me) st.push_back(e);
        else {
          isBridge[e] = 1;
          // auto [a, b] = edges[e];
          // bridges.emplace_back(a, b);
        }
      }
    }
  return top;
}

template<class F>
void bicomps(F f) {
  num.assign(sz(ed), 0);
  FOR(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
}
} using namespace BC;

const int maxn = 3e5+5;
int comp[maxn];

void dfs(int i, int c) {
  comp[i] = c;
  for (auto [j, e]: ed[i]) {
    if (comp[j] != -1 || isBridge[e]) continue;
    dfs(j, c);
  }
}

vector<int> adj[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  ed.resize(N);
  isBridge.resize(M);
  int eid = 0;
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    ed[a].emplace_back(b, eid);
    ed[b].emplace_back(a, eid++);
  }
  bicomps([&](const auto& v){});

  memset(comp, -1, sizeof comp);
  int c = 0;
  F0R(i, N) {
    if (comp[i] == -1) {
      dfs(i, c++);
    }
  }
  F0R(i, N) {
    for (auto [j, e]: ed[i]) {
      adj[comp[i]].push_back(comp[j]);
    }
  }

  auto furthest = [&](int i) -> pair<int, int> {
    vector<int> dist(c, maxn);
    queue<int> q; q.push(i);
    dist[i] = 0;
    pair<int, int> mx = {0, i};
    while (!q.empty()) {
      int j = q.front(); q.pop();
      ckmax(mx, {dist[j], j});
      for (int k: adj[j]) {
        if (dist[k] > dist[j] + 1) {
          dist[k] = dist[j] + 1;
          q.push(k);
        }
      }
    }
    return mx;
  };
  auto [d1, z1] = furthest(0);
  auto [d2, z2] = furthest(z1);
  cout << d2 << '\n';
}
