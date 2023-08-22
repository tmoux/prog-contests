#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

vector<int> add(vector<int> a, vector<int> b) {
  int carry = 0;
  vector<int> c(sz(a));
  F0R(i, sz(a)) {
    int s = a[i] + b[i] + carry;
    c[i] = s % 2;
    carry = s / 2;
  }
  assert(carry == 0);
  return c;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int a, b, k; cin >> a >> b >> k;
  int oa = a, ob = b;
  if (k == 0) {
    cout << "Yes\n";
    REP(2) {
      F0R(i, b) cout << 1;
      F0R(i, a) cout << 0;
      cout << '\n';
    }
  }
  else if (a == 0 || b == 1) {
    cout << "No\n";
  }
  else if (k <= a+b-2) {
    vector<int> X(a+b), Y(a+b);
    X[0] = Y[0] = 1;
    b--;
    int i = 1;
    while (1) {
      if (a > 1 && k < a+b-1) {
        X[i] = Y[i] = 0;
        i++;
        a--;
      }
      else if (b > 1 && k < a+b-1) {
        X[i] = Y[i] = 1;
        i++;
        b--;
      }
      else {
        assert(k == a+b-1);
        vector<int> z(a+b), y(a+b);
        F0R(i, k) z[i] = 1;
        F0R(i, b) y[i] = 1;
        vector<int> x = add(y, z);
        F0R(i, sz(x)) X[sz(X)-1-i] = x[i];
        F0R(i, sz(y)) Y[sz(Y)-1-i] = y[i];
        break;
      }
    }
    assert(count(all(X), 0) == oa);
    assert(count(all(X), 1) == ob);
    assert(count(all(Y), 0) == oa);
    assert(count(all(Y), 1) == ob);
    cout << "Yes\n";
    for (auto x: X) cout << x;
    cout << '\n';
    for (auto x: Y) cout << x;
    cout << '\n';
  }
  else cout << "No\n";
}
