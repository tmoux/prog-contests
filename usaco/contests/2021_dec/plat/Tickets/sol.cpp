#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

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

const ll INF = 1e18;
struct Edge
{
  int to;
  ll weight;
};

struct Ticket {
  int c, p, a, b;
  bool operator<(const Ticket& rhs) const {
    return a < rhs.a;
  }
};

struct Node {/*{{{*/
  int s, e, m;
  int mnl, mxr;
  Ticket t;
  Node *l, *r;

  Node(int a, int b, const vector<Ticket>& tickets) {
    s = a;
    e = b;
    if (s != e) {
      m = (s+e)/2;
      l = new Node(s,m, tickets);
      r = new Node(m+1,e, tickets);
      pull();
    }
    else {
      t = tickets[s];
      mnl = t.a;
      mxr = t.b;
      l = nullptr;
      r = nullptr;
    }
  }

  void pull() {
    if (s != e) {
      mnl = min(l->mnl, r->mnl);
      mxr = max(l->mxr, r->mxr);
    }
  }

  void remove(vector<int>& rems, int i) {
    if (mnl > i || mxr < i) return;
    if (s == e) {
      if(t.a <= i && i <= t.b) {
        rems.push_back(s);
        mnl = 2e9;
        mxr = -1;
      }
      return;
    }
    l->remove(rems, i);
    r->remove(rems, i);
    pull();
  }
};/*}}}*/

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, K; cin >> N >> K;
  vector<vector<Edge>> adj(N+K);
  vector<Ticket> tickets;
  for (int i = 0; i < K; i++) {
    int c, p, a, b; cin >> c >> p >> a >> b;
    c--; a--; b--;
    tickets.push_back({c, p, a, b});
  }
  sort(all(tickets));
  for (int i = 0; i < K; i++) {
    adj[i+N].push_back({tickets[i].c, tickets[i].p});
  }

  auto dijkstra = [&](int source, const vector<vector<Edge>>& adj) {
    vector<ll> dist(sz(adj), INF);
    dist[source] = 0;
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    pq.push({0LL,source});

    Node *root = new Node(0, sz(tickets)-1, tickets);
    while (!pq.empty()) {
      auto [d, u] = pq.top(); pq.pop();
      if (d > dist[u]) continue;
      if (u < N) { //checkpoint
        vector<int> relevantTickets;
        root->remove(relevantTickets, u);
        for (int id: relevantTickets) {
          int v = id + N;
          if (dist[v] > dist[u]) {
            dist[v] = dist[u];
            pq.push({dist[v],v});
          }
        }
      }
      else { // ticket or finish node
        for (const Edge& e: adj[u]) {
          int v = e.to;
          ll weight = e.weight;
          if (dist[v] > dist[u] + weight) {
            dist[v] = dist[u] + weight;
            pq.push({dist[v],v});
          }
        }
      }
    }
    return dist;
  };

  auto d1 = dijkstra(0, adj);
  auto dn = dijkstra(N-1, adj);

  vector<ll> finishTime(N+K);
  F0R(i, N+K) {
    finishTime[i] = d1[i] + dn[i];
  }

  auto adj2 = adj;
  adj2.resize(N+K+1);
  F0R(i, N+K) {
    if (finishTime[i] < INF) adj2[N+K].push_back({i, finishTime[i]});
  }
  // output answer
  auto ans = dijkstra(N+K, adj2);
  F0R(i, N) {
    cout << (ans[i] < INF ? ans[i] : -1) << '\n';
  }
}
