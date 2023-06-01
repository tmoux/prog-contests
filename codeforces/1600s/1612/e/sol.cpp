#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

struct Frac {
  ll a, b;
  bool operator<(const Frac& rhs) const {
    return a * rhs.b < rhs.a * b;
  }

  friend ostream& operator<<(ostream& o, const Frac& v)  {
    return o << v.a << " / " << v.b << endl;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  const int maxn = 200001, maxk = 20;
  vector<int> s(maxn);
  vector<vector<int>> v(maxn);
  F0R(i, N) {
    int m, k; cin >> m >> k;
    v[m].push_back(k);
    s[m] += k;
  }

  pair<Frac, vector<int>> bestSmall = {{-1, 1}, {}};
  FOR(t, 1, maxk+1) {
    vector<pair<int, int>> vs;
    FOR(j, 1, maxn) {
      int sum = 0;
      for (int k: v[j]) {
        sum += min(t, k);
      }
      vs.push_back({sum, j});
    }
    sort(all(vs), greater());
    int num = 0;
    vector<int> tr;
    F0R(i, t) {
      num += vs[i].first;
      tr.push_back(vs[i].second);
    }
    Frac f = {num, t};
    if (bestSmall.first < f) {
      bestSmall = {f, tr};
    }
  }

  cout << sz(bestSmall.second) << '\n';
  for (auto i: bestSmall.second) {
    cout << i << ' ';
  }
  cout << '\n';
}
