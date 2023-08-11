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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, K; cin >> N >> K;
  vector<std::optional<int>> A(N);
  vector<int> ans(N);
  F0R(i, N) {
    string s; cin >> s;
    if (sz(s) == 1 && s[0] == '?') {
      A[i] = std::nullopt;
    }
    else A[i] = ans[i] = stoi(s);
  }
  vector<vector<pair<int, int>>> v(K); // (type, val)
  FOR(i, 0, N) {
    if (A[i]) {
      int x = *A[i];
      v[i % K].emplace_back(0, x);
    }
    else {
      v[i % K].emplace_back(1, i);
    }
  }

  bool poss = true;
  for (auto& vec: v) {
    // cout << vec << endl;
    const int INF = 1e9+1e5+5;
    vec.push_back({0, INF});
    int cur = -INF;
    vector<int> block;
    for (auto [t, x]: vec) {
      if (t == 0) {
        if (x <= cur || x-cur-1 < sz(block)) {
          // cout << "false because " << x << ' ' << cur << endl;
          poss = false;
        }
        else {
          // (cur, x)
          if (cur >= 0) {
            F0R(i, sz(block)) {
              ans[block[i]] = cur + 1 + i;
            }
          }
          else if (x <= 0) {
            F0Rd(i, sz(block)) {
              // DEBUG(x);
              // cout << "setting " << block[i] << ' ' << x-1-(sz(block)-1-i) << endl;
              ans[block[i]] = x - 1 - (sz(block)-1-i);
            }
          }
          else {
            int l = 0, r = 1;
            deque<int> indices;
            while (sz(indices) < sz(block)) {
              if (abs(l) <= abs(r) && l > cur) {
                indices.push_front(l--);
              }
              else if (abs(r) <= abs(l) && r < x) {
                indices.push_back(r++);
              }
              else if (l > cur) {
                indices.push_front(l--);
              }
              else if (r < x) {
                indices.push_back(r++);
              }
              else assert(false);
            }
            F0R(i, sz(block)) {
              ans[block[i]] = indices[i];
            }
          }

          cur = x;
          block.clear();
        }
      }
      else block.push_back(x);
    }
  }

  if (!poss) {
    cout << "Incorrect sequence\n";
  }
  else {
    F0R(i, N) cout << ans[i] << " \n"[i == N-1];
  }
}
