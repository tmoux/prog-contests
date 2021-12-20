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

const int maxn = 2e5+5;
int parent[maxn]; //memset to -1
int detTime[maxn];
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
    ckmin(detTime[x], detTime[y]);
}

int solve() {
  int n, k; cin >> n >> k;
  map<int, set<pair<int,int>>> rows, cols;
  vector<pair<int, int>> pos(n);
  F0R(i, n) {
    int x, y, timer; cin >> x >> y >> timer;
    pos[i] = {x, y};
    detTime[i] = timer;
    rows[x].insert({y, i});
    cols[y].insert({x, i});
  }

  F0R(i, n) {
    auto [x, y] = pos[i];
    //find left
    auto it = rows[x].lower_bound({y, i});
    if (it != rows[x].begin() && y - prev(it)->first <= k) {
      Union(i, prev(it)->second);
    }
    //find right
    it = rows[x].upper_bound({y, i});
    if (it != rows[x].end() && it->first - y <= k) {
      Union(i, it->second);
    }
    //find up
    it = cols[y].lower_bound({x, i});
    if (it != cols[y].begin() && x - prev(it)->first <= k) {
      Union(i, prev(it)->second);
    }
    //find down
    it = cols[y].upper_bound({x, i});
    if (it != cols[y].end() && it->first - x <= k) {
      Union(i, it->second);
    }
  }

  map<int, int> times;
  F0R(i, n) {
    times[Find(i)] = detTime[Find(i)];
  }
  vector<int> v;
  for (auto [_, t]: times) v.push_back(t);
  sort(all(v), greater<int>());

  //cout << "SZ" << sz(v) << endl;
  //cout << v << endl;
  int ans = sz(v)-1;
  for (int i = 0; i < sz(v); i++) {
    ckmin(ans, max(max(0, i-1), v[i]));
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    memset(parent, -1, sizeof parent);
    cout << solve() << '\n';
  }
}
