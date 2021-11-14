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
// }}}

string solve(const string& s) {
  vector<int> d;
  for (char c: s) d.push_back(c-'0');
  int n = sz(d);

  auto is_consec = [](int a, int b) {
    if (a == -1 || b == -1) return false;
    return ((a+1) % 10) == b;
  };
  vector<vector<pair<int,int>>> events(10);
  set<int> indices;
  F0R(i, n) indices.insert(i);
  for (int i = 0; i < n-1; i++) {
    if (is_consec(d[i], d[i+1])) {
      events[d[i]].push_back({i,i+1});
    }
  }

  for (int i = 0; ; i = (i+1) % 10) {
    /*
    for (int j = 0; j < n; j++) {
      cout << d[j] << ' ';
    }
    cout << '\n';
    cout << i << ": " << sz(events[i]) << endl;
    */
    if (i == 0) {
      bool stop = true;
      for (int j = 0; j < 10; j++) {
        if (!events[j].empty()) stop = false;
      }
      if (stop) break;
    }
    while (!events[i].empty()) {
      auto [a, b] = events[i].back();
      events[i].pop_back();
      //cout << "checking " << a << ' ' << b << endl;
      if (is_consec(d[a], d[b])) {
        d[a] = (d[a] + 2) % 10;
        d[b] = -1;
        indices.erase(b);

        //update position a
        auto it = indices.upper_bound(a);
        if (it != indices.end() && is_consec(d[a], d[*it])) {
          events[d[a]].push_back({a,*it});
        }
        //update previous position a
        it = indices.lower_bound(a);
        if (it != indices.begin() && is_consec(d[*prev(it)], d[a])) {
          events[d[*prev(it)]].push_back({*prev(it), a});
        }
      }
    }
  }

  string ans;
  F0R(i, n) if (d[i] != -1) ans += d[i]+'0';
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    int n; cin >> n;
    string s; cin >> s;
    cout << "Case #" << tc << ": " << solve(s) << endl;
  }
}
