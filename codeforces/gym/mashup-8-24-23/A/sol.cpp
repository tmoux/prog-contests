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

using vi = vector<int>;
using pii = pair<int, int>;

namespace BC {
  vi num, st;
  vector<vector<pii>> ed;
  vector<array<int, 3>> bridges;
  vector<array<int, 3>> edges;
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
          if (up == me) { // BCC (list of edges)
            st.push_back(e);
            f(vi(st.begin() + si, st.end()));
            st.resize(si);
          }
          else if (up < me) st.push_back(e);
          else { // BRIDGE
            bridges.push_back(edges[e]);
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

int N, M;

struct PushRelabel {
	struct Edge {
		int dest, back;
		ll f, c;
	};
	vector<vector<Edge>> g;
	vector<ll> ec;
	vector<Edge*> cur;
	vector<vi> hs; vi H;
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

	void addEdge(int s, int t, ll cap, ll rcap=0) {
		if (s == t) return;
		g[s].push_back({t, sz(g[t]), 0, cap});
		g[t].push_back({s, sz(g[s])-1, 0, rcap});
	}

	void addFlow(Edge& e, ll f) {
		Edge &back = g[e.dest][e.back];
		if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
		e.f += f; e.c -= f; ec[e.dest] += f;
		back.f -= f; back.c += f; ec[back.dest] -= f;
	}
	ll calc(int s, int t) {
		int v = sz(g); H[s] = v; ec[t] = 1;
		vi co(2*v); co[0] = v-1;
		FOR(i,0,v) cur[i] = g[i].data();
		for (Edge& e : g[s]) addFlow(e, e.c);

		for (int hi = 0;;) {
			while (hs[hi].empty()) if (!hi--) return -ec[s];
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ec[u] > 0)  // discharge u
				if (cur[u] == g[u].data() + sz(g[u])) {
					H[u] = 1e9;
					for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
						H[u] = H[e.dest]+1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						FOR(i,0,v) if (hi < H[i] && H[i] < v)
							--co[H[i]], H[i] = v + 1;
					hi = H[u];
				} else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
					addFlow(*cur[u], min(ec[u], cur[u]->c));
				else ++cur[u];
		}
	}
	bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  ed.resize(N);
  edges.resize(M);

  map<int, int> compress;
  int cnt = 0;
  F0R(i, M) {
    int u, v, c; cin >> u >> v >> c;
    if (compress.count(c)) c = compress[c];
    else {
      compress[c] = cnt++;
      c = compress[c];
    }
    u--, v--;
    edges[i] = {u, v, c};
    ed[u].emplace_back(v, i);
    ed[v].emplace_back(u, i);
  }
  // cout << compress << endl;

  vector<vector<int>> cycles;
  bicomps([&](const vi& edgelist) {
    vector<int> v;
    for (auto e: edgelist) {
      v.push_back(edges[e][2]);
    }
    cycles.push_back(v);
  });

  int n = sz(bridges) + sz(cycles), m = cnt;
  int counter = 0;
  int source = n + m, sink = n + m + 1;
  PushRelabel graph(n + m + 2);

  for (auto [u, v, c]: bridges) {
    graph.addEdge(source, counter, 1);
    graph.addEdge(counter, n + c, 1);
    counter++;
  }
  for (const auto& v: cycles) {
    graph.addEdge(source, counter, sz(v) - 1);
    for (auto c: v) {
      graph.addEdge(counter, n + c, 1);
    }
    counter++;
  }
  for (int c = 0; c < m; c++) {
    graph.addEdge(n + c, sink, 1);
  }

  cout << graph.calc(source, sink) << '\n';
}
