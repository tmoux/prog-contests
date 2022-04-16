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

vector<int> diffs;
vector<int> v;
int osum = 0;
void precomp() {
  set<int> pow2;
  for (int i = 0; i < 30; i++) {
    pow2.insert(1<<i);
    diffs.push_back(1<<i);
  }
  // cout << diffs << endl;

  for (int i = 2; sz(v) < (100 - sz(pow2) - 1); i += 2) {
    if (!pow2.count(i)) {
      v.push_back(i);
      osum += i;
    }
  }
  // cout << v << endl;
  // cout << osum << endl;
}
void solve() {
  int N; cin >> N;
  assert(N == 100);
  vector<int> a;
  for (auto x: diffs) {
    a.push_back(x);
  }
  for (auto x: v) a.push_back(x);
  a.push_back(osum);
  assert(sz(a) == N);

  for (auto x: a) {
    cout << x << ' ';
  }
  cout << endl;
  vector<int> b(N);
  F0R(i, N) cin >> b[i];

  vector<int> ans1, ans2;
  for (auto x: v) ans1.push_back(x);
  ans2.push_back(osum);

  // assert(accumulate(all(ans1), 0LL) == accumulate(all(ans2), 0LL));

  ll sum = 0;
  F0R(i, N) {
    if (sum - b[i] >= -1000000000) {
      sum -= b[i];
      ans1.push_back(b[i]);
    }
    else {
      sum += b[i];
      ans2.push_back(b[i]);
    }
  }
  if (sum > 0) {
    swap(ans1, ans2);
  }
  else sum *= -1;

  ll S = accumulate(all(diffs), 0LL);
  // cerr << S << endl;
  int target = (S - sum) / 2;
  /*
  if (target > (1<<29)) {
    target = S - target;
    swap(ans1, ans2);
  }
  */
  // cerr << target << endl;

  FOR(i, 0, 30) {
    if (target & (1<<i)) {
      ans1.push_back(1<<i);
    }
    else {
      ans2.push_back(1<<i);
    }
  }
  // cerr << ans1 << endl;
  // cerr << accumulate(all(ans1), 0LL) << endl;
  // cerr << accumulate(all(ans2), 0LL) << endl;
  // cerr << accumulate(all(ans1), 0LL) - accumulate(all(ans2), 0LL) << endl;
  assert(accumulate(all(ans1), 0LL) == accumulate(all(ans2), 0LL));
  for (auto x: ans1) {
    cout << x << ' ';
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  precomp();
  int T; cin >> T;
  while (T--) solve();
}
