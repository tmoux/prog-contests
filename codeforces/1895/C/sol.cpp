#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

ll solve() {
  int N; cin >> N;

  map<int, map<int, int>> mp;
  vector<pair<vector<int>, int>> V;
  F0R(i, N) {
    string s; cin >> s;
    vector<int> v;
    for (char c: s) v.push_back(c - '0');
    int sum = std::accumulate(all(v), 0);
    mp[sz(s)][sum]++;
    V.push_back({v, sum});
  }

  ll num_eq = 0, num_pairs = 0;
  for (const auto& [v, sum]: V) {
    num_eq += mp[sz(v)][sum];
    for (int len = 1; len <= 5; len++) {
      if ((sz(v) + len) % 2 == 0) {
        int k = (sz(v) + len) / 2;
        if (k < sz(v)) {
          int s1 = 0;
          for (int i = 0; i < k; i++) s1 += v[i];
          num_pairs += mp[len][s1 - (sum - s1)];
          // mysum += mp[len][s1 - (sum - s1)];
          // cout << len << ' ' << s1-(sum-s1) << ": " << mp[len][s1 - (sum - s1)] << endl;
          //

          int s2 = 0;
          for (int i = 0; i < k; i++) s2 += v[sz(v)-1-i];
          num_pairs += mp[len][s2 - (sum - s2)];
        }
      }
    }
    // DEBUG(mysum);
  }
  // DEBUG(num_eq);
  // DEBUG(num_pairs);
  return num_eq + num_pairs;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T = 1;
  while (T--) cout << solve() << '\n';
}
