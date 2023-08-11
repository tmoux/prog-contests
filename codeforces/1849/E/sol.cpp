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

const int maxn = 1e6+6;
int N, A[maxn];

class Tracker {
  private:
    ll cur;
  public:
    set<pair<int, int>> s;
    Tracker() : cur(0) {
      s.insert({-1, -1});
    }
    void add(int i, int t) {
      int prev = s.rbegin()->first;
      if (t == 0) cur += i - prev;
      s.insert({i, t});
    }
    void remove(int i, int t) {
      auto it = s.find({i, t});
      assert(it != s.end());
      if (it->second == 0) {
        cur -= it->first - prev(it)->first;
      }
      if (next(it) != s.end() && next(it)->second == 0) {
        cur -= next(it)->first - it->first;
      }
      s.erase(it);
      it = s.lower_bound({i, t});
      if (it != s.end() && it->second == 0) {
        cur += it->first - prev(it)->first;
      }
    }
    ll getans() {
      return cur;
    }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) {
    cin >> A[i];
  }

  stack<pair<int, int>> mns, mxs;
  Tracker tracker;
  ll ans = 0;
  F0R(i, N) {
    while (!mns.empty() && mns.top().first > A[i]) {
      tracker.remove(mns.top().second, 0);
      mns.pop();
    }
    while (!mxs.empty() && mxs.top().first < A[i]) {
      tracker.remove(mxs.top().second, 1);
      mxs.pop();
    }
    ans += tracker.getans();

    mns.push({A[i], i});
    tracker.add(i, 0);
    mxs.push({A[i], i});
    tracker.add(i, 1);
  }
  cout << ans << '\n';
}
