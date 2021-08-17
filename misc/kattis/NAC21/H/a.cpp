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

const int maxn = 155;
int n, m, k;

struct Edge {
  int to;
  bool special;
};

vector<vector<Edge>> adj;

vector<int> st;
bool isCycle(int i, int p, vector<bool>& visited, const vector<set<int>>& adj, vector<int>& ans) {
  st.push_back(i);
  visited[i] = true;
  /*
  cout << "visiting " << i+1 << '\n';
  for (int j: adj[i]) {
    cout << j+1 << ' ';
  }
  cout << '\n';
  */
  for (auto j: adj[i]) {
    if (j == p) continue;
    if (!visited[j]) {
      if (isCycle(j, i, visited, adj, ans)) return true;
    }
    else {
      //found cycle
      cout << st << endl;
      cout << i+1 << ' ' << j+1 << '\n';
      ans.clear();
      for (int k = st.size()-1; k >= 0; k--) {
        ans.push_back(st[k]);
        if (st[k] == j) break;
      }
      return true;
    }
  }
  //st.pop_back();
  return false;
}

vector<int> findCycle(int sz, const vector<set<int>>& adj) {
  vector<bool> visited(sz, false);
  vector<int> ans;
  for (int i = 0; i < sz; i++) {
    if (!visited[i]) {
      st.clear();
      //cout << "searching " << i << '\n';
      if (isCycle(i, -1, visited, adj, ans)) {
        //cout << "found it" << '\n';
        return ans;
      }
    }
  }
  return {};
}

void buildPath(int i, int p, const vector<set<int>>& adj, vector<int>& path) {
  path.push_back(i);
  for (auto j: adj[i]) {
    if (j == p) continue;
    buildPath(j, i, adj, path);
  }
}

bool isadj[maxn][maxn];

vector<int> uncompressPath(const vector<int>& v, const vector<vector<int>>& paths) {
  vector<int> ret;
  for (int i: v) {
    if (paths[i].empty()) {
      ret.push_back(i);
    }
    else {
      if (ret.empty() || ret.back() != paths[i][0]) {
        for (int j: paths[i]) {
          ret.push_back(j);
        }
      }
      else {

      }
    }
  }
  return ret;
}

void outputPath(const vector<int>& v) {
  cout << v.size() << '\n';
  for (int i: v) {
    cout << i+1 << '\n';
  }
}

void printGraph(const vector<set<int>>& adj) {
  cout << "Graph " << '\n';
  F0R(i, adj.size()) {
    for (int j: adj[i]) {
        cout << i+1 << ' ' << j+1 << '\n';
    }
  }
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m >> k;
  adj.resize(n);
  vector<int> specialCount(n);
  vector<bool> deleted(n,false);
  F0R(i, m) {
    int a, b; cin >> a >> b;
    a--; b--;

    isadj[a][b] = true;
    isadj[b][a] = true;
    if (i < k) {
      specialCount[a]++;
      specialCount[b]++;
      adj[a].push_back({b,true});
      adj[b].push_back({a,true});
    }
    else {
      adj[a].push_back({b,false});
      adj[b].push_back({a,false});
    }
  }
  F0R(i, n) {
    if (specialCount[i] > 2) {
      deleted[i] = true;
      for (auto e: adj[i]) {
        if (e.special) {
          deleted[e.to] = true;
        }
      }
    }
  }
  //Find cycle of only special edges

  vector<set<int>> specialGraph(n);
  F0R(i, n) {
    for (auto e: adj[i]) {
      if (!deleted[i] && !deleted[e.to] && e.special) {
        specialGraph[i].insert(e.to);
     }
    }
  }
  auto specialCycle = findCycle(n, specialGraph);
  if (!specialCycle.empty()) {
    outputPath(specialCycle);
    return 0;
  }

  //printGraph(specialGraph);

  //Now special edges form a set of disjoint paths.
  //Compress each path into 2 nodes and find cycles
  
  vector<set<int>> compressedGraph(2*n);
  vector<vector<int>> paths(2*n);
  vector<int> nodeMap(n);
  F0R(i, n) nodeMap[i] = i;

  int numNodes = n;
  vector<bool> visited(n,false);

  F0R(i, n) {
    if (!visited[i] && specialGraph[i].size() == 1) {
      vector<int> path;
      buildPath(i, i, specialGraph, path);
      assert(path.size() >= 2);
      for (int j: path) {
        visited[j] = true;
      }
      int start = path[0];
      int end = path.back();

      nodeMap[start] = numNodes++;
      nodeMap[end] = numNodes++;

      paths[nodeMap[start]] = path;
      reverse(all(path));
      paths[nodeMap[end]] = path;

      //Add edge if not already edge between start and end
      //Avoid duplicate edges
      if (!isadj[start][end]) {
        compressedGraph[nodeMap[start]].insert(nodeMap[end]);
        compressedGraph[nodeMap[end]].insert(nodeMap[start]);
      }

      //delete every thing not in the start or end
      for (int j: path) {
        if (j != start && j != end) deleted[j] = true;
      }
    }
  }

  F0R(i, n) {
    if (deleted[i]) continue;
    for (auto e: adj[i]) {
      if (deleted[e.to]) continue;
      compressedGraph[nodeMap[i]].insert(nodeMap[e.to]);
      compressedGraph[nodeMap[e.to]].insert(nodeMap[i]);
    }
  }

  printGraph(compressedGraph);

  auto cycle = findCycle(numNodes, compressedGraph);
  if (!cycle.empty()) {
    //cout << cycle << '\n';
    //cout << endl;
    auto uncompressed = uncompressPath(cycle, paths);
    outputPath(uncompressed);
    return 0;
  }

  cout << -1 << '\n';
}
