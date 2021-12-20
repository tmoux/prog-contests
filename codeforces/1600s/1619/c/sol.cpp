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

vector<int> b;

void rec(const vector<int>& a, vector<int>& res, string_view s) {
  if (!b.empty()) return;

  if (s.empty()) {
    //cout << "trying " << res << endl;
    //cout << a << endl;
    if (sz(a) <= sz(res)) {
      vector<int> na = a;
      while (sz(na) < sz(res)) na.insert(na.begin(), 0);
      assert(sz(na) == sz(res));

      vector<int> pb;
      bool poss = true;
      F0R(i, sz(res)) {
        int digit = res[i] - na[i];
        if (0 <= digit && digit <= 9) {
          pb.push_back(digit);
        }
        else {
          poss = false;
          break;
        }
      }
      if (poss) {
        b = pb;
        return;
      }
    }
  }
  else {
  //try take 1
  res.push_back(s[0]-'0');
  rec(a, res, s.substr(1));
  res.pop_back();

  //try take 2
  if (sz(s) >= 2 && s[0] == '1') {
    res.push_back(10*(s[0]-'0') + (s[1]-'0'));
    rec(a, res, s.substr(2));
    res.pop_back();
  }
  }
}

void solve() {
  string a, s; cin >> a >> s;
  b.clear();
  vector<int> ad;
  F0R(i, sz(a)) {
    ad.push_back(a[i]-'0');
  }
  vector<int> res;
  rec(ad, res, s);

  if (!b.empty()) {
    //cout << b << endl;
    //return;
    int i = 0;
    while (i < sz(b) && b[i] == 0) i++;
    for (; i < sz(b); i++) {
      cout << b[i];
    }
    cout << '\n';
  }
  else {
    cout << -1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
