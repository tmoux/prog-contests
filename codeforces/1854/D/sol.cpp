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

int N;

void answer(vector<int> V) {
  sort(all(V));
  cout << "! " << sz(V) << ' ';
  for (auto x: V) cout << x << ' ';
  cout << endl;
}
int Q = 0;
int query(int u, int k, vector<int> S) {
  assert(k > 0);
  assert(sz(S) > 0);
  assert(++Q <= 2000);
  cout << "? " << u << ' ' << k << ' ' << sz(S) << ' ';
  for (auto x: S) cout << x << ' ';
  cout << endl;

  int r; cin >> r;
  return r;
}

int get_kth(int u, int k) {
  vector<int> v(N); iota(all(v), 1);
  while (sz(v) > 1) {
    vector<int> v1, v2;
    F0R(i, sz(v)) {
      (i % 2 == 0 ? v1 : v2).push_back(v[i]);
    }
    v = query(u, k, v1) ? v1 : v2;
  }
  return v[0];
}

int is_cycle_length(int u, int l) {
  return query(u, l, {u});
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int K = 63;
  cin >> N;

  int s = get_kth(1, N);
  vector<int> C = {s};
  REP(K-1) {
    int i = C.back();
    int j = get_kth(i, 1);
    if (find(all(C), j) != C.end()) break;
    else C.push_back(j);
  }
  if (sz(C) < N) {
    while (1) {
      vector<int> adds;
      for (int i = 1; i <= N; i++) {
        if (find(all(C), i) != C.end()) continue;
        if (query(i, K, C)) adds.push_back(i);
      }
      if (adds.empty()) break;
      else {
        K *= 2;
        for (auto i: adds) C.push_back(i);
      }
    }
  }
  answer(C);
}
