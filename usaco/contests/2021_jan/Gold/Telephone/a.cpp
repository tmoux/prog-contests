#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;
const int maxn = 5e4+4, maxk = 55;
int N, K;
int b[maxn];
int S[maxk][maxk];

struct Edge {
  int to; 
  ll w;
};
vector<Edge> adj[maxn];

ll dijkstra(int s, int t) {
  set<pair<ll,int>> setds;
  vector<ll> dist(N,INF);
  setds.insert({0,s});
  dist[s] = 0;
  while (!setds.empty()) {
    auto tmp = *(setds.begin());
    setds.erase(setds.begin());
    int u = tmp.second;
    for (Edge& e: adj[u]) {
      int v = e.to;
      ll weight = e.w;
      if (dist[v] > dist[u] + weight) {
        if (dist[v] != INF) {
          auto it = setds.find({dist[v],v});
          if (it != setds.end()) setds.erase(it);
          //setds.erase(setds.find({dist[v],v}));
        }
        dist[v] = dist[u] + weight;
        setds.insert({dist[v],v});
      }
    }
  }
  /*
  for (int i = 0; i < N; i++) {
    cout << i << ": " << dist[i] << endl;
  }
  */
  return dist[t];
}

set<int> ss[maxk];

void add_edge(int i, int j) {
  adj[i].push_back({j,abs(i-j)});
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    cin >> b[i];
    b[i]--;
    ss[b[i]].insert(i);
  }
  for (int i = 0; i < K; i++) {
    for (int j = 0; j < K; j++) {
      char c; cin >> c;
      S[i][j] = c-'0';
    }
  }
  //create graph
  for (int i = 0; i < N; i++) {
    if (i == 0) {
      for (int j = 0; j < N; j++) {
        if (i != j && S[b[i]][b[j]]) {
          add_edge(i,j);
        }
      }
    }
    else {
      for (int k = 0; k < K; k++) {
        if (S[b[i]][k]) {
          auto it = ss[k].upper_bound(i);
          if (it != ss[k].end()) {
            add_edge(i,*it);
          }
          it = ss[k].lower_bound(i);
          if (it != ss[k].begin()) {
            --it;
            add_edge(i,*it);
          }
        }
      }
      //add edge i -> N-1
      if (S[b[i]][b[N-1]]) {
        add_edge(i,N-1);
      }
    }
  }

  ll ans = dijkstra(0,N-1);
  cout << (ans < INF ? ans : -1) << '\n';
}
