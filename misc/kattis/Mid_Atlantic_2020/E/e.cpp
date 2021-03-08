#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
 
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
 
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
 
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
 
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int MOD = 1000000007;
const char nl = '\n';
const int MX = 100001; //check the limits, dummy

struct Edge
{
    int from, to; ll capacity, cost;
    Edge(int f, int t, ll c1, ll c2) {
        from = f; to = t; cost = c1; capacity = c2;
    }
};

vector<vector<ll>> adj, cost, capacity;

const ll INF = 1e18;

void shortest_paths(int n, int v0, vector<ll>& d, vector<ll>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

ll min_cost_flow(int N, vector<Edge> edges, ll K, int s, int t) {
    adj.assign(N, vector<ll>());
    cost.assign(N, vector<ll>(N, 0));
    capacity.assign(N, vector<ll>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    ll flow = 0;
    ll cost = 0;
    vector<ll> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        ll f = K - flow;
        ll cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if (flow < K)
        return -1;
    else
        return cost;
}

//Mincost Flow by https://cp-algorithms.com/graph/min_cost_flow.html

void solve() {

    int N; cin >> N;
    vpl A(N); F0R(i, N) cin >> A[i].f >> A[i].s;
    sort(all(A));
    F0R(i, N-1) A[i].s--;
    F0R(it, 2) {
        int K = 2*N+2;
        vector<Edge> E;
        F0R(i, N-1) {
            E.pb(Edge(0, i+1, (ll) 0, (ll) 1));
        }
        F0R(i, N) {
            E.pb(Edge(N+1+i, 2*N+1, (ll) 0, (ll) A[i].s));
        }
        F0R(i, N) {
            FOR(j, i+1, N) {
                ll cost = A[i].f ^ A[j].f;
                if (it) cost = (1ll << 30) - cost;
                E.pb(Edge(i+1, N+j+1, (ll) cost, (ll) 1));
            }
        }
        /*trav(a, E) {
            cout << a.from << " " << a.to << " " << ((1ll << 30) - a.cost) << " " << a.capacity << nl;
        }
        cout << "DONE" << nl;*/
        ll ans = min_cost_flow(K, E, N-1, 0, 2*N+1);
        if (it) {
            ans = (1ll << 30) * (N-1) - ans;
        }
        cout << ans << " ";
    }
    cout << nl;

}
 
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    

    int T = 1;
//    cin >> T;
    while(T--) {
        solve();
    }

	return 0;
}
 
// read the question correctly (ll vs int)
// template by bqi343

