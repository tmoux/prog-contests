#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef long double ld; // change to double if appropriate
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define F0Rd(i, a) for (int i = (a) - 1; i >= 0; i--)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

const char nl = '\n';

/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow. cap[i][j] != cap[j][i] is allowed; double edges are not.
 *  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: Approximately O(E^2)
 */

// #include <bits/extc++.h> /// include-line, keep-include

#include <ext/pb_ds/priority_queue.hpp>

const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;

using pii = pair<int, int>;
struct MCMF {
  int N;
  vector<vi> ed, red;
  vector<VL> cap, flow, cost;
  vi seen;
  VL dist, pi;
  vector<pii> par;

  MCMF(int N) :
    N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
    seen(N), dist(N), pi(N), par(N) {}

  void addEdge(int from, int to, ll cap, ll cost) {
    this->cap[from][to] = cap;
    this->cost[from][to] = cost;
    ed[from].push_back(to);
    red[to].push_back(from);
  }

  void path(int s) {
    fill(all(seen), 0);
    fill(all(dist), INF);
    dist[s] = 0; ll di;

    __gnu_pbds::priority_queue<pair<ll, int>> q;
    vector<decltype(q)::point_iterator> its(N);
    q.push({0, s});

    auto relax = [&](int i, ll cap, ll cost, int dir) {
      ll val = di - pi[i] + cost;
      if (cap && val < dist[i]) {
        dist[i] = val;
        par[i] = {s, dir};
        if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
        else q.modify(its[i], {-dist[i], i});
      }
    };

    while (!q.empty()) {
      s = q.top().second; q.pop();
      seen[s] = 1; di = dist[s] + pi[s];
      for (int i : ed[s]) if (!seen[i])
        relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
      for (int i : red[s]) if (!seen[i])
        relax(i, flow[i][s], -cost[i][s], 0);
    }
    FOR(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
  }

  pair<ll, ll> maxflow(int s, int t) {
    ll totflow = 0, totcost = 0;
    while (path(s), seen[t]) {
      ll fl = INF;
      for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
        fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
      totflow += fl;
      for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
        if (r) flow[p][x] += fl;
        else flow[x][p] -= fl;
    }
    FOR(i,0,N) FOR(j,0,N) totcost += cost[i][j] * flow[i][j];
    return {totflow, totcost};
  }

  // If some costs can be negative, call this before maxflow:
  void setpi(int s) { // (otherwise, leave this out)
    fill(all(pi), INF); pi[s] = 0;
    int it = N, ch = 1; ll v;
    while (ch-- && it--)
      FOR(i,0,N) if (pi[i] != INF)
        for (int to : ed[i]) if (cap[i][to])
          if ((v = pi[i] + cost[i][to]) < pi[to])
            pi[to] = v, ch = 1;
    assert(it >= 0); // negative cost cycle
  }
};

//template<typename flow_t = int, typename cost_t = int>
//struct mcSFlow{
//    struct Edge{
//        cost_t c;
//        flow_t f;
//        int to, rev;
//        Edge(int _to, cost_t _c, flow_t _f, int _rev):c(_c), f(_f), to(_to), rev(_rev){}
//    };
//    const cost_t INFCOST = numeric_limits<cost_t>::max()/2;
//    const cost_t INFFLOW = numeric_limits<flow_t>::max()/2;
//    cost_t epsilon;
//    int N, S, T;
//    vector<vector<Edge> > G;
//    vector<unsigned int> isEnqueued, state;
//    mcSFlow(int _N, int _S, int _T):epsilon(0), N(_N), S(_S), T(_T), G(_N){}
//    void add_edge(int a, int b, cost_t cost, flow_t cap){
//        if(a==b){assert(cost>=0); return;}
//        cost*=N;// to preserve integer-values
//        epsilon = max(epsilon, abs(cost));
//        assert(a>=0&&a<N&&b>=0&&b<N);
//        G[a].emplace_back(b, cost, cap, G[b].size());
//        G[b].emplace_back(a, -cost, 0, G[a].size()-1);
//    }
//    flow_t calc_max_flow(){ // Dinic max-flow
//        vector<flow_t> dist(N), state(N);
//        vector<Edge*> path(N);
//        auto cmp = [](Edge*a, Edge*b){return a->f < b->f;};
//        flow_t addFlow, retflow=0;;
//        do{
//            fill(dist.begin(), dist.end(), -1);
//            dist[S]=0;
//            auto head = state.begin(), tail = state.begin();
//            for(*tail++ = S;head!=tail;++head){
//                for(Edge const&e:G[*head]){
//                    if(e.f && dist[e.to]==-1){
//                        dist[e.to] = dist[*head]+1;
//                        *tail++=e.to;
//                    }
//                }
//            }
//            addFlow = 0;
//            fill(state.begin(), state.end(), 0);
//            auto top = path.begin();
//            Edge dummy(S, 0, INFFLOW, -1);
//            *top++ = &dummy;
//            while(top != path.begin()){
//                int n = (*prev(top))->to;
//                if(n==T){
//                    auto next_top = min_element(path.begin(), top, cmp);
//                    flow_t flow = (*next_top)->f;
//                    while(--top!=path.begin()){
//                        Edge &e=**top, &f=G[e.to][e.rev];
//                        e.f-=flow;
//                        f.f+=flow;
//                    }
//                    addFlow=1;
//                    retflow+=flow;
//                    top = next_top;
//                    continue;
//                }
//                for(int &i=state[n], i_max = G[n].size(), need = dist[n]+1;;++i){
//                    if(i==i_max){
//                        dist[n]=-1;
//                        --top;
//                        break;
//                    }
//                    if(dist[G[n][i].to] == need && G[n][i].f){
//                        *top++ = &G[n][i];
//                        break;
//                    }
//                }
//            }
//        }while(addFlow);
//        return retflow;
//    }
//    vector<flow_t> excess;
//    vector<cost_t> h;
//    void push(Edge &e, flow_t amt){
//        //cerr << "push: " << G[e.to][e.rev].to << " -> " << e.to << " (" << e.f << "/" << e.c << ") : " << amt << "\n";
//        if(e.f < amt) amt=e.f;
//        e.f-=amt;
//        excess[e.to]+=amt;
//        G[e.to][e.rev].f+=amt;
//        excess[G[e.to][e.rev].to]-=amt;
//    }
//    void relabel(int vertex){
//        cost_t newHeight = -INFCOST;
//        for(unsigned int i=0;i<G[vertex].size();++i){
//            Edge const&e = G[vertex][i];
//            if(e.f && newHeight < h[e.to]-e.c){
//                newHeight = h[e.to] - e.c;
//                state[vertex] = i;
//            }
//        }
//        h[vertex] = newHeight - epsilon;
//    }
//    const int scale=2;
//    pair<flow_t, cost_t> minCostFlow(){
//        cost_t retCost = 0;
//        for(int i=0;i<N;++i){
//            for(Edge &e:G[i]){
//                retCost += e.c*(e.f);
//            }
//        }
//        //find feasible flow
//        flow_t retFlow = calc_max_flow();
//        excess.resize(N);h.resize(N);
//        queue<int> q;
//        isEnqueued.assign(N, 0); state.assign(N,0);
//        for(;epsilon;epsilon>>=scale){
//            //refine
//            fill(state.begin(), state.end(), 0);
//            for(int i=0;i<N;++i)
//                for(auto &e:G[i])
//                    if(h[i] + e.c - h[e.to] < 0 && e.f) push(e, e.f);
//            for(int i=0;i<N;++i){
//                if(excess[i]>0){
//                    q.push(i);
//                    isEnqueued[i]=1;
//                }
//            }
//            while(!q.empty()){
//                int cur=q.front();q.pop();
//                isEnqueued[cur]=0;
//                // discharge
//                while(excess[cur]>0){
//                    if(state[cur] == G[cur].size()){
//                        relabel(cur);
//                    }
//                    for(unsigned int &i=state[cur], max_i = G[cur].size();i<max_i;++i){
//                        Edge &e=G[cur][i];
//                        if(h[cur] + e.c - h[e.to] < 0){
//                            push(e, excess[cur]);
//                            if(excess[e.to]>0 && isEnqueued[e.to]==0){
//                                q.push(e.to);
//                                isEnqueued[e.to]=1;
//                            }
//                            if(excess[cur]==0) break;
//                        }
//                    }
//                }
//            }
//            if(epsilon>1 && epsilon>>scale==0){
//                epsilon = 1<<scale;
//            }
//        }
//        for(int i=0;i<N;++i){
//            for(Edge &e:G[i]){
//                retCost -= e.c*(e.f);
//            }
//        }
//        //cerr << " -> " << retFlow << " / " << retCost << " bzw. " << retCost/2/N << "\n";
//        return make_pair(retFlow, retCost/2/N);
//    }
//    flow_t getFlow(Edge const &e){
//        return G[e.to][e.rev].f;
//    }
//};

template<typename flow_t = int, typename cost_t = int>
struct mcSFlow{
    struct Edge{
        cost_t c;
        flow_t f;
        int to, rev;
        Edge(int _to, cost_t _c, flow_t _f, int _rev):c(_c), f(_f), to(_to), rev(_rev){}
    };
    static constexpr cost_t INFCOST = numeric_limits<cost_t>::max()/2;
    cost_t eps;
    int N, S, T;
    vector<vector<Edge> > G;
    vector<unsigned int> isq, cur;
    vector<flow_t> ex;
    vector<cost_t> h;
    mcSFlow(int _N, int _S, int _T):eps(0), N(_N), S(_S), T(_T), G(_N){}
    void add_edge(int a, int b, cost_t cost, flow_t cap){
		assert(cap>=0);
        assert(a>=0&&a<N&&b>=0&&b<N);
        if(a==b){assert(cost>=0); return;}
        cost*=N;
        eps = max(eps, abs(cost));
        G[a].emplace_back(b, cost, cap, G[b].size());
        G[b].emplace_back(a, -cost, 0, G[a].size()-1);
    }
    void add_flow(Edge& e, flow_t f) {
        Edge &back = G[e.to][e.rev];
        if (!ex[e.to] && f)
            hs[h[e.to]].push_back(e.to);
        e.f -= f; ex[e.to] += f;
        back.f += f; ex[back.to] -= f;
    }
    vector<vector<int> > hs;
    vector<int> co;
    flow_t max_flow() {
        ex.assign(N, 0);
        h.assign(N, 0); hs.resize(2*N);
        co.assign(2*N, 0); cur.assign(N, 0);
        h[S] = N;
        ex[T] = 1;
        co[0] = N-1;
        for(auto &e:G[S]) add_flow(e, e.f);
        if(hs[0].size())
        for (int hi = 0;hi>=0;) {
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ex[u] > 0) { // discharge u
                if (cur[u] == G[u].size()) {
                    h[u] = 1e9;
                    for(unsigned int i=0;i<G[u].size();++i){
                        auto &e = G[u][i];
                        if (e.f && h[u] > h[e.to]+1){
                            h[u] = h[e.to]+1, cur[u] = i;
                        }
                    }
                    if (++co[h[u]], !--co[hi] && hi < N)
                        for(int i=0;i<N;++i)
                            if (hi < h[i] && h[i] < N){
                                --co[h[i]];
                                h[i] = N + 1;
                            }
                    hi = h[u];
                } else if (G[u][cur[u]].f && h[u] == h[G[u][cur[u]].to]+1)
                    add_flow(G[u][cur[u]], min(ex[u], G[u][cur[u]].f));
                else ++cur[u];
			}
            while (hi>=0 && hs[hi].empty()) --hi;
        }
        return -ex[S];
    }
    void push(Edge &e, flow_t amt){
        if(e.f < amt) amt=e.f;
        e.f-=amt; ex[e.to]+=amt;
        G[e.to][e.rev].f+=amt; ex[G[e.to][e.rev].to]-=amt;
    }
    void relabel(int vertex){
        cost_t newHeight = -INFCOST;
        for(unsigned int i=0;i<G[vertex].size();++i){
            Edge const&e = G[vertex][i];
            if(e.f && newHeight < h[e.to]-e.c){
                newHeight = h[e.to] - e.c;
                cur[vertex] = i;
            }
        }
        h[vertex] = newHeight - eps;
    }
    static constexpr int scale=2;
    pair<flow_t, cost_t> minCostMaxFlow(){
        cost_t retCost = 0;
        for(int i=0;i<N;++i)
            for(Edge &e:G[i])
                retCost += e.c*(e.f);
        //find max-flow
        flow_t retFlow = max_flow();
        h.assign(N, 0); ex.assign(N, 0);
        isq.assign(N, 0); cur.assign(N,0);
        queue<int> q;
        for(;eps;eps>>=scale){
            //refine
            fill(cur.begin(), cur.end(), 0);
            for(int i=0;i<N;++i)
                for(auto &e:G[i])
                    if(h[i] + e.c - h[e.to] < 0 && e.f) push(e, e.f);
            for(int i=0;i<N;++i){
                if(ex[i]>0){
                    q.push(i);
                    isq[i]=1;
                }
            }
            // make flow feasible
            while(!q.empty()){
                int u=q.front();q.pop();
                isq[u]=0;
                while(ex[u]>0){
                    if(cur[u] == G[u].size())
                        relabel(u);
                    for(unsigned int &i=cur[u], max_i = G[u].size();i<max_i;++i){
                        Edge &e=G[u][i];
                        if(h[u] + e.c - h[e.to] < 0){
                            push(e, ex[u]);
                            if(ex[e.to]>0 && isq[e.to]==0){
                                q.push(e.to);
                                isq[e.to]=1;
                            }
                            if(ex[u]==0) break;
                        }
                    }
                }
            }
            if(eps>1 && eps>>scale==0){
                eps = 1<<scale;
            }
        }
        for(int i=0;i<N;++i){
            for(Edge &e:G[i]){
                retCost -= e.c*(e.f);
            }
        }
        return make_pair(retFlow, retCost/2/N);
    }
    flow_t getFlow(Edge const &e){
        return G[e.to][e.rev].f;
    }
};

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>;


void solve() {
  int n, c1, c2;
  cin >> n;
  vi cnt(n, 0);
  F0R(i, n) {
    int t; cin >> t; t--;
    cnt[t]++;
  }
  c1 = n;
  c2 = c1 + 1;
  // MCMF t(n+2);
  mcSFlow<int, int> t(n+2, c1, c2);
  F0R(i, n) {
    // t.addEdge(c1, i, cnt[i], 0);
    // t.addEdge(i, c2, 1, 0);
    t.add_edge(c1, i, 0, cnt[i]);
    t.add_edge(i, c2, 0, 1);
  }
  int e; cin >> e;
  F0R(i, e) {
    int a, b; cin >> a >> b;
    a--, b--;
    // t.addEdge(a, b, 1000, 1);
    // t.addEdge(b, a, 1000, 1);
    t.add_edge(a, b, 1, 1000);
    t.add_edge(b, a, 1, 1000);
  }
  cout << t.minCostMaxFlow().second << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int T; cin >> T;
  while (T--) solve();
  return 0;
}
