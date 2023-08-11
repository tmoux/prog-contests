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

const int X = 1000005;
const int BAD = -1e9;

struct DSU {
  vector<int> par, root;
  DSU() {
    par = vector<int>(X, BAD);
    root.resize(X);
  }
  void addNode(int i) {
    assert(i >= 0);
    par[i] = -1;
    root[i] = i;
  }
  int findParent(int i) {
    if (par[i] == BAD) addNode(i);  
    return par[i] < 0 ? i : par[i] = findParent(par[i]);
  }
  void Union(int x, int y) { // keep x's root
    if (par[x] == BAD) addNode(x);
    if (par[y] == BAD) addNode(y);
    x = findParent(x);
    y = findParent(y);
    if (x == y) return;
    if (par[x] > par[y]) {
      par[x] += par[y];
      par[y] = x;
    }
    else {
      par[y] += par[x];
      root[y] = root[x];
      par[x] = y;
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int q; cin >> q;

  DSU dsu;
  int loc[X], mp[X];
  memset(loc, -1, sizeof loc);
  memset(mp, -1, sizeof mp);

  int pt = 0;

  auto create = [&](int i) {
    if (mp[i] == -1) {
      mp[i] = pt;
      loc[pt] = i;
      pt++;
    }
  };

  vector<int> arr;
  while (q--) {
    int t; cin >> t;
    if (t == 1) {
      int x; cin >> x;
      create(x);
      arr.push_back(mp[x]);
    }
    else if (t == 2) {
      int x, y; cin >> x >> y;
      if (x == y) continue;
      create(x);
      create(y);
      dsu.Union(mp[y], mp[x]);

      mp[x] = pt;
      loc[pt] = x;
      pt++;
    }

    /*
    for (ll i: arr) {
      cout << (dsu.root[dsu.findParent(i)] % X) << ' ';
    }
    cout << '\n';
    */
  }

  for (ll i: arr) {
    cout << (loc[dsu.root[dsu.findParent(i)]]) << ' ';
  }
  cout << '\n';
}
