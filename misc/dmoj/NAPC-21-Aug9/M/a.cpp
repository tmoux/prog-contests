#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto &a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
#define f first
#define s second

template <class T>
bool ckmin(T &a, const T &b)
{
	return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename T>
ostream &operator<<(ostream &o, const vector<T> &v)
{
	o << "[";
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		o << *it;
		if (next(it) != v.end())
			o << ", ";
	}
	o << "]";
	return o;
}

int sqr(int x)
{
	return x * x;
}

int dist(array<int, 2> a, array<int, 2> b)
{
	return sqr(a[0] - b[0]) + sqr(a[1] - b[1]);
}

struct MCMF { 
	using F = ll; using C = ll; // flow type, cost type
	#define V vector
	struct Edge { int to, rev; F flo, cap; C cost; };
	int N; V<C> p, dist; vpi pre; V<V<Edge>> adj;
	void init(int _N) { N = _N;
		p.resize(N), adj.resize(N), dist.resize(N), pre.resize(N); }
	void ae(int u, int v, F cap, C cost) { assert(cap >= 0); 
		adj[u].push_back({v,sz(adj[v]),0,cap,cost}); 
		adj[v].push_back({u,sz(adj[u])-1,0,0,-cost});
	} // use asserts, don't try smth dumb
	bool path(int s, int t) { // find lowest cost path to send flow through
		const C inf = numeric_limits<C>::max(); dist.assign(N,inf);
		using T = pair<C,int>; priority_queue<T,vector<T>,greater<T>> todo; 
		todo.push({dist[s] = 0,s}); 
		while (sz(todo)) { // Dijkstra
			T x = todo.top(); todo.pop(); if (x.f > dist[x.s]) continue;
			trav(e,adj[x.s]) { // all weights should be non-negative
				if (e.flo < e.cap && ckmin(dist[e.to],x.f+e.cost+p[x.s]-p[e.to]))
					pre[e.to] = {x.s,e.rev}, todo.push({dist[e.to],e.to});
			}
		} // if costs are doubles, add some EPS so you 
		// don't traverse ~0-weight cycle repeatedly
		return dist[t] != inf; // return flow
	}
	pair<F,C> calc(int s, int t) { assert(s != t);
		F0R(_,N) F0R(i,N) trav(e,adj[i]) // Bellman-Ford
			if (e.cap) ckmin(p[e.to],p[i]+e.cost);
		F totFlow = 0; C totCost = 0;
		while (path(s,t)) { // p -> potentials for Dijkstra
			F0R(i,N) p[i] += dist[i]; // don't matter for unreachable nodes
			F df = numeric_limits<F>::max();
			for (int x = t; x != s; x = pre[x].f) {
				Edge& e = adj[pre[x].f][adj[x][pre[x].s].rev]; 
				ckmin(df,e.cap-e.flo); }
			totFlow += df; totCost += (p[t]-p[s])*df;
			for (int x = t; x != s; x = pre[x].f) {
				Edge& e = adj[x][pre[x].s]; e.flo -= df;
				adj[pre[x].f][e.rev].flo += df;
			}
		} // get max flow you can send along path
		return {totFlow,totCost};
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;
	MCMF mcmf;
	mcmf.init(2*N+2);
	int source = 2 * N;
	int sink = 2 * N + 1;

	const int INF = 100000;
	vector<array<int, 2>> male(N), female(N);
	for (int i = 0; i < N; i++)
	{
		cin >> male[i][0] >> male[i][1];
		mcmf.ae(source, i, 1, 0);
	}
	for (int i = 0; i < N; i++)
	{
		cin >> female[i][0] >> female[i][1];
		mcmf.ae(i + N, sink, 1, 0);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			mcmf.ae(i, j+N, 1, dist(male[i], female[j]));
		}
	}

	cout << mcmf.calc(source, sink).second << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << i << ' ' << j << ": " << mcmf.adj[i][j+N].rev << '\n';
		}
	}
}
