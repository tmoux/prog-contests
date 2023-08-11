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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> a(n+1), b(n+1);
  vector<ll> delta(n+1, 0), fx(n+1, 0);
  FOR(i, 1, n+1) cin >> a[i];
  FOR(i, 1, n+1) cin >> b[i];
  for (int i = 2; i <= n; i++) {
    delta[i] = b[i] - a[i];
  }
  fx[1] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 2*i; j <= n; j += i) {
      delta[j] -= delta[i];
      fx[j] -= fx[i];
    }
  }

  ll A = 0, B = 0;
  vector<pair<int,int>> switches;
  for (int i = 1; i <= n; i++) {
    if (fx[i] > 0) {
      fx[i] *= -1;
      delta[i] *= -1;
    }
    if (fx[i] == 0) {
      A += abs(delta[i]);
    }
    else {
      A += delta[i];
      B += fx[i];
    }

    if (fx[i] != 0) {
      assert(fx[i] == -1);
      switches.push_back({delta[i], i});
    }
  }

  int q; cin >> q;
  vector<ll> ans(q);
  vector<pair<int,int>> queries;
  F0R(i, q) {
    int x; cin >> x;
    x = x - a[1];
    queries.push_back({x, i});
  }
  sort(all(queries));
  sort(all(switches)); reverse(all(switches));

  for (auto [x, id]: queries) {
    while (!switches.empty() && switches.back().first < x) {
      int i = switches.back().second;
      switches.pop_back();
      A -= 2*delta[i];
      B -= 2*fx[i];
    }

    ans[id] = A + B * x;
  }
  F0R(i, q) {
    cout << ans[i] << '\n';
  }
}
