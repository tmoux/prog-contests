#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

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

const int maxn = 1e5+5;
int n, m1, m2;

//Edges must be added between nodes in different components (treat as DSU)
//If just one forest with k components, then k-1 edges can be added (forming a single tree)
//As long as both forests have > 1 components, we should be able to find a valid edge.
//Find the smallest component in forest 1. Call these nodes 1..i. Look to see if we can add any of the edges (1..i, i+1..n). Then once we have found an edge, merge the two components.
//When always merging the smaller component, we can guarantee that whenever a node in a component is examined, it will be merge into a component at least twice the size. So, each node will only be examined (with at most n other nodes) a total of log(n) times.
//So the total running time should be O(n * log^2(n) * ackermann(n)).

struct DSU {
  int sz;
  vector<int> par;
  set<pair<int,int>> components; //ordered by size

  DSU(int _n) {
    sz = _n;
    par = vector<int>(sz, -1);
    for (int i = 0; i < sz; i++) components.insert({-par[i],i});
  }

  int num_components() {
    return components.size();
  }

  int get_smallest_component() {
    return components.begin()->second;
  }

  //Find the root of the component containing i, applying path compression
  int find_root(int i) {
    return par[i] < 0 ? i : par[i] = find_root(par[i]);
  }

  //Returns true if a and b were in different components
  bool merge(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b) return false; 
    if (-par[a] < -par[b]) swap(a,b);
    components.erase({-par[b],b}); 
    components.erase({-par[a],a}); 
    par[a] += par[b];
    par[b] = a;
    components.insert({-par[a],a});
    return true;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m1 >> m2;
  DSU f1(n), f2(n);
  for (int i = 0; i < m1; i++) {
    int a, b; cin >> a >> b;
    a--; b--;
    f1.merge(a,b);
  }
  for (int i = 0; i < m2; i++) {
    int a, b; cin >> a >> b;
    a--; b--;
    f2.merge(a,b);
  }

  vector<pair<int,int>> ans;
  while (f1.num_components() > 1 && f2.num_components() > 1) {
    int i = f1.get_smallest_component();
    pair<int,int> edge = {-1,-1};
    vector<int> comp;
    for (int j = 0; j < n; j++) if (f1.find_root(i) == f1.find_root(j)) comp.push_back(j);
    for (int k: comp) {
      for (int j = 0; j < n; j++) {
        if (f1.find_root(j) != f1.find_root(k) && f2.find_root(j) != f2.find_root(k)) {
          edge = {j,k};
          goto done;
        }
      }
    }

    done:
    //cout << "adding " << edge.first << ' ' << edge.second << endl;
    assert(edge.first != -1);
    ans.push_back(edge);
    f1.merge(edge.first, edge.second);
    f2.merge(edge.first, edge.second);
  }

  //output
  cout << ans.size() << '\n';
  for (auto e: ans) {
    cout << e.first+1 << ' ' << e.second+1 << '\n';
  }
}
