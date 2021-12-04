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

void test() {
  int N = 10;
  int mu[N][N][N];
  memset(mu, 0, sizeof mu);
  auto special = [](int a, int b, int c) {
    vector<int> v;
    if (a) v.push_back(a);
    if (b) v.push_back(b);
    if (c) v.push_back(c);
    for (int i = 0; i+1 < sz(v); i++) {
      if (v[i] > v[i+1]) return false;
    }
    return true;
  };
  auto tuple_less = [](vector<int> a, vector<int> b) {
    for (int i = 0; i < sz(a); i++) {
      if (a[i] > b[i]) return false;
    }
    return true;
  };
  F0R(i, N) {
    F0R(j, N) {
      F0R(k, N) {
        int ac = special(i, j, k) ? 1 : 0;        
        F0R(i1, i+1) {
          F0R(j1, j+1) {
            F0R(k1, k+1) {
              if (i1 == i && j1 == j && k1 == k) continue;
              vector<int> a = {i, j, k};
              vector<int> b = {i1, j1, k1};
              ac -= mu[i1][j1][k1];
            }
          }
        }
        mu[i][j][k] = ac;
        if (mu[i][j][k] == -1)
          printf("(%d, %d, %d): %d, %d\n", i, j, k, special(i, j, k), mu[i][j][k]);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  test();
}
