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
  int T; cin >> T;
  while (T--) {
    int n; cin >> n;
    string s; cin >> s;

    auto is_sorted = [](string s) {
      for (int i = 1; i < sz(s); i++) {
        if (s[i] < s[i-1]) return false;
      }
      return true;
    };

    if (is_sorted(s)) {
      cout << 0 << '\n';
    }
    else {
      vector<int> v;
      int r = n-1;
      for (int l = 0; l < n; l++) {
        if (s[l] == '1') {
          while (r > l && s[r] == '1') r--;
          if (r > l && s[r] == '0') {
            v.push_back(l);
            v.push_back(r);
            r--;
          }
          else break;
        }
      }
      sort(all(v));

      for (int i = 0; i < sz(v)/2; i++) {
        swap(s[v[i]], s[v[sz(v)-1-i]]);
      }

      cout << 1 << '\n';
      cout << sz(v) << ' ';
      for (int i: v) cout << i+1 << ' ';
      cout << '\n';

      //cout << s << endl;
      assert(is_sorted(s));
    }
  }
}
