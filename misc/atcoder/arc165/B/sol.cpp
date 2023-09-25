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

template<typename T>
void output_vector(const vector<T>& v) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << (next(it) == v.end() ? '\n' : ' ');
  }
}

template<typename T>
void output_vector(const vector<T>& v, int offset) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << (*it + offset) << (next(it) == v.end() ? '\n' : ' ');
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, K; cin >> N >> K;
  vector<int> P(N);
  F0R(i, N) {
    cin >> P[i];
  }
  vector<int> num_inc(N);
  for (int i = 0; i < N; i++) {
    if (i == 0) num_inc[i] = 1;
    else num_inc[i] = P[i] > P[i-1] ? 1 + num_inc[i-1] : 1;
  }
  if (*max_element(all(num_inc)) >= K) {
    output_vector(P);
    return 0;
  }

  vector<int> nxt(N);
  set<int> s;
  vector<pair<int, int>> v;
  F0R(i, N) v.push_back({P[i], i});
  sort(all(v));
  for (auto [x, i]: v) {
    auto it = s.upper_bound(i);
    nxt[i] = it == s.end() ? N : *it;
    s.insert(i);
  }

  pair<int, int> best = {N-K, N-K};
  F0R(i, N) {
    int nl = num_inc[i];
    int nr = nxt[i] - i;
    // cout << i << ": " << nl << ' ' << nr << endl;
    if (nl + nr - 1 >= K) {
      int j = i - nl + 1;
      if (i+1 > best.first || (i+1 == best.first && j < best.second)) {
        best = {i+1, j};
      }
    }
  }

  int idx = best.second;
  DEBUG(best);
  DEBUG(idx);
  sort(P.begin() + idx, P.begin() + idx + K);
  output_vector(P);
}