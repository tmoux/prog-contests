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
#define f first
#define s second
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

// https://cp-algorithms.com/graph/edmonds_karp.html
struct MaxFlow {
  const int INF = 2e9;
  int n;
  vector<vector<int>> capacity; //matrix of capacities
  vector<vector<int>> adj; //adjacency list of undirected graph

  MaxFlow(int _n) {
    n = _n;
    capacity = vector<vector<int>>(n, vector<int>(n,0));
    adj.resize(n);
  }

  void add_edge(int a, int b, int c) {
    capacity[a][b] = c;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int bfs(int s, int t, vector<int>& parent) {
      fill(parent.begin(), parent.end(), -1);
      parent[s] = -2;
      queue<pair<int, int>> q;
      q.push({s, INF});

      while (!q.empty()) {
          int cur = q.front().first;
          int flow = q.front().second;
          q.pop();

          for (int next : adj[cur]) {
              if (parent[next] == -1 && capacity[cur][next]) {
                  parent[next] = cur;
                  int new_flow = min(flow, capacity[cur][next]);
                  if (next == t)
                      return new_flow;
                  q.push({next, new_flow});
              }
          }
      }

      return 0;
  }

  int maxflow(int s, int t) {
      int flow = 0;
      vector<int> parent(n);
      int new_flow;

      while (new_flow = bfs(s, t, parent)) {
          flow += new_flow;
          int cur = t;
          while (cur != s) {
              int prev = parent[cur];
              capacity[prev][cur] -= new_flow;
              capacity[cur][prev] += new_flow;
              cur = prev;
          }
      }

      return flow;
  }
};


const int maxn = 105;
int N, M;
char grid[maxn][maxn];

const int dx[] = {0,1,0,-1};
const int dy[] = {1,0,-1,0};
int cv(int i, int j) {
  return i*M+j;
}
bool valid(int i, int j) {
  return 0 <= i && i < N && 0 <= j && j < M;
}

bool isEdge(int i, int j) {
  return i == 0 || i == N-1 || j == 0 || j == M-1;
}

int toComp[maxn][maxn];
vector<vector<pair<int,int>>> comps;

void floodfill(int i, int j, int counter) {
  toComp[i][j] = counter;
  comps[counter].push_back({i,j});
  F0R(k,4) {
    int ni = i + dx[k];
    int nj = j + dy[k];
    if (valid(ni,nj) && grid[i][j] == grid[ni][nj] && toComp[ni][nj] == -1) {
      floodfill(ni,nj,counter);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i,N) {
    F0R(j,M) {
      char c; cin >> c;
      grid[i][j] = c;
      toComp[i][j] = -1;
    }
  }
  int counter = 0;
  F0R(i,N) {
    F0R(j,M) {
      if (toComp[i][j] == -1) {
        comps.push_back(vector<pair<int,int>>());
        floodfill(i,j,counter);
        counter++;
      }
    }
  }

  int ans = 0;
  vector<bool> isEdgeComp(counter,false);
  F0R(i,counter) {
    for (auto p: comps[i]) {
      if (isEdge(p.first,p.second)) {
        isEdgeComp[i] = true;
        ans++;
        break;
      }
    }
  }

  int source = counter;
  int sink = counter+1;
  MaxFlow EK = MaxFlow(counter+2);

  F0R(i,counter) if (!isEdgeComp[i]) {
    int x = comps[i][0].first;
    int y = comps[i][0].second;

    if (grid[x][y] == '0') {
      //set<int> adds;
      for (auto p: comps[i]) {
        int x = p.first;
        int y = p.second;
        F0R(k,4) {
          int nx = x + dx[k];
          int ny = y + dy[k];
          int j = toComp[nx][ny];
          if (valid(nx,ny) && grid[x][y] != grid[nx][ny] && !isEdgeComp[j]) {
            EK.add_edge(i,j,1);
          }
        }
      }
      /*
      for (int j: adds) {
        EK.add_edge(i,j,1);
      }
      */
    }
  }

  F0R(i,counter) {
    if (comps[i].size() > 0) {
      int x = comps[i][0].first;
      int y = comps[i][0].second;
      if (grid[x][y] == '0') {
        EK.add_edge(source,i,1);
      }
      else {
        EK.add_edge(i,sink,1);
      }
    }
  }

  ans += EK.maxflow(source,sink);
  cout << ans << '\n';
}
