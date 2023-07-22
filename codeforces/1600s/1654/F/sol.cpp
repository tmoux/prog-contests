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

using T = pair<pair<int, int>, int>;
void radixSort(vector<T>& v, int N) {
  // (stable) sort by second component, then by first
  vector<T> output(sz(v));
  vector<int> cnt(N);
  F0R(i, sz(v)) {
    cnt[v[i].first.second]++;
  }
  FOR(i, 1, N) cnt[i] += cnt[i-1];
  F0Rd(i, sz(v)) {
    int p = --cnt[v[i].first.second];
    output[p] = v[i];
  }
  v = output;
  fill(all(cnt), 0);
  F0R(i, sz(v)) {
    cnt[v[i].first.first]++;
  }
  FOR(i, 1, N) cnt[i] += cnt[i-1];
  F0Rd(i, sz(v)) {
    int p = --cnt[v[i].first.first];
    output[p] = v[i];
  }
  v = output;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  string s; cin >> s;
  vector<int> v(1 << N); iota(all(v), 0);
  sort(all(v), [&](int i, int j) { return s[i] < s[j];} );
  vector<int> pos(1 << N);
  int c = -1;
  F0R(i, 1 << N) {
    if (i == 0 || s[v[i]] > s[v[i-1]]) {
      pos[v[i]] = ++c;
    }
    else pos[v[i]] = c;
  }
  for (int k = 0; k < N; k++) {
    vector<T> nv;
    F0R(i, 1 << N) {
      nv.push_back({{pos[i], pos[i ^ (1 << k)]}, i});
    }
    radixSort(nv, 1 << N);
    int c = -1;
    F0R(i, 1 << N) {
      if (i == 0 || nv[i].first > nv[i-1].first) {
        pos[nv[i].second] = ++c;
      }
      else pos[nv[i].second] = c;
    }
  }

  int i = -1;
  F0R(j, 1 << N) {
    if (pos[j] == 0) {
      i = j;
      break;
    }
  }
  F0R(j, 1 << N) {
    cout << s[i ^ j];
  }
  cout << '\n';
}
