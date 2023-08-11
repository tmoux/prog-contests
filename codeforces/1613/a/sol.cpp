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

void solve() {
  int x1, p1; cin >> x1 >> p1;
  int x2, p2; cin >> x2 >> p2;

  auto digits = [](int x) {
    vector<int> v;
    while (x > 0) {
      v.push_back(x % 10);
      x /= 10;
    }
    reverse(all(v));
    return v;
  };
  auto len = [](int x) {
    int r = 0;
    while (x > 0) {
      r++;
      x /= 10;
    }
    return r;
  };
  int len_1 = len(x1) + p1;
  int len_2 = len(x2) + p2;

  if (len_1 < len_2) {
    cout << "<\n";
    return;
  }
  else if (len_1 > len_2) {
    cout << ">\n";
    return;
  }
  else {
    auto d1 = digits(x1); 
    auto d2 = digits(x2); 
    while (sz(d1) < sz(d2)) d1.push_back(0);
    while (sz(d2) < sz(d1)) d2.push_back(0);
    for (int i = 0; i < min(sz(d1), sz(d2)); i++) {
      if (d1[i] < d2[i]) {
        cout << "<\n";
        return;
      }
      else if (d1[i] > d2[i]) {
        cout << ">\n";
        return;
      }
    }
    cout << "=\n";
    return;

    /*
    for (int i = 0; i < min(sz(d1), sz(d2)); i++) {
      int c1 = i < sz(d1) ? d1[i] : 0;
      int c2 = i < sz(d2) ? d2[i] : 0;
      if (c1 < c2) {
        cout << "<\n";
        return;
      }
      else if (c1 > c2) {
        cout << ">\n";
        return;
      }
    }
    cout << "=\n";
    */
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
