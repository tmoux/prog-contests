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

struct Point {
  int x, y;
};

const int maxn = 505;
int n, m, q;
Point pt[maxn];
vector<int> adj[maxn];

double dist(Point a, Point b) {
  return hypot(a.x-b.x,a.y-b.y);
}

struct Vertex {
  int a, b; //Node positions
  double weight;
  Vertex(int _a, int _b) {
    a = _a;
    b = _b;
    weight = dist(pt[a], pt[b]);
  }

  bool operator<(const Vertex& rhs) const {
    return weight < rhs.weight;
  }
};

vector<int> adjacents[maxn*maxn];

vector<double> ans;

struct DSU {
  vector<int> vs;
  set<int> queries;
};

int cv(int a, int b) {
  return a*n + b;
}

DSU* parent[maxn*maxn];

void merge(int a, int b, double weight) {
  auto pa = parent[a];  
  auto pb = parent[b];
  if (pa != pb) {
    //merge b into a    
    if (pa->vs.size() < pb->vs.size()) {
      swap(pa,pb);
    }
    for (int p: pb->vs) {
      pa->vs.push_back(p);
      parent[p] = pa;
    }
    for (int query: pb->queries) {
      if (pa->queries.count(query)) {
        pa->queries.erase(query);
        ans[query] = weight;
      }
      else {
        pa->queries.insert(query);
      }
    }
  }
}

bool seen[maxn*maxn];
  
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> pt[i].x >> pt[i].y;
  }
  cin >> m;
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b; 
    a--; b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<Vertex> vertices;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        vertices.push_back(Vertex(i,j));
        int index = cv(i,j);
        for (int k: adj[i]) {
          adjacents[index].push_back(cv(k,j));
        }
        for (int k: adj[j]) {
          adjacents[index].push_back(cv(i,k));
        }

        parent[index] = new DSU;
        parent[index]->vs.clear();
        parent[index]->queries.clear();

        parent[index]->vs.push_back(index);
      }
    }
  }
  sort(all(vertices)); reverse(all(vertices));
  /*
  for (auto v: vertices) {
    cout << v.a << ' ' << v.b << ' ' << v.weight << '\n';
  }
  */
  cin >> q;
  ans.resize(q);
  for (int i = 0; i < q; i++) {
    int a, b; cin >> a >> b;
    a--; b--;
    parent[cv(a,b)]->queries.insert(i);
    parent[cv(b,a)]->queries.insert(i);
  }

  for (auto vertex: vertices) {
    double weight = vertex.weight;
    int v = cv(vertex.a, vertex.b);
    for (int w: adjacents[v]) {
      if (seen[w]) {
        merge(v, w, weight);
      }
    }
    seen[v] = true;
  }

  cout << fixed << setprecision(10);
  for (int i = 0; i < q; i++) {
    cout << ans[i] << '\n';
  }
}
