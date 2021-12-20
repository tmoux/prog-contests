#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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

template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) 
  requires Container<U<T>> && (!requires(std::ostream o, T a) { operator<<(o, a); })
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

const int n = 500;
int grid[n][n], dp[n][n];

struct Edge {
  int to, weight;
};

const ll INF = 1e18;
vector<Edge> adj[n*n];

vector<ll> dijkstra(int source) {
	vector<ll> dist(n*n,INF);
	dist[source] = 0;
	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
	pq.push({0LL,source});
	while (!pq.empty()) {
		int u = pq.top().second; 
        int d = pq.top().first;
		pq.pop();
        if (d > dist[u]) continue; 
		for (Edge& e: adj[u]) {
			int v = e.to;
			ll weight = e.weight;
			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				pq.push({dist[v],v});
			}
		}
	}
	return dist;
}

int cv(int i, int j) {
  return i*n + j;
}

bool valid(int i, int j) {
  return 0 <= i && i < n && 0 <= j && j < n;
}

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  F0R(i, n/5) {
    string s; cin >> s;
    F0R(j, n/5) {
      grid[i][j] = s[j] - '0';
      F0R(ii, 5) {
        F0R(jj, 5) {
          grid[i+ii*n/5][j+jj*n/5] = ((grid[i][j] + (ii + jj) - 1) % 9) + 1;
        }
      }
    }
  }

  F0R(i, n) {
    F0R(j, n) {
      F0R(k, 4) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (valid(ni, nj)) {
          adj[cv(i, j)].push_back({cv(ni, nj), grid[ni][nj]});
        }
      }
    }
  }


  auto d = dijkstra(0);
  cout << d[cv(n-1, n-1)] << endl;
}
