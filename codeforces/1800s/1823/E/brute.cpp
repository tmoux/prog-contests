#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const int maxn = 2e5+5;
int N, L, R;
int G[maxn];

int mex(vector<int> v) {
 sort(all(v)); v.erase(unique(all(v)), v.end());
 F0R(i, sz(v)) {
   if (v[i] != i) return i;
 }
 return sz(v);
}

bool period(int i, int k) {
  F0R(a, k) {
    for (int j = i+a; j <= N; j += k) {
      if (G[j] != G[i+a]) return false;
    }
  }
  return true;
}

int P[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> L >> R;
  for (int i = 1; i <= N; i++) {
    vector<int> v;
    for (int k = L; k <= R; k++) {
      for (int j = 0; j + k <= i; j++) {
        int a = j;
        int b = i - (j + k);
        v.push_back(G[a] ^ G[b]);
      }
    }
    G[i] = mex(v);
    // cout << i << ": " << G[i] << endl;
  }

  for (int i = 1; i <= N; i++) {
    vector<int> v;
    for (int k = L; k <= min(i, R); k++) {
      v.push_back(G[i-k]);
    }
    cout << i << ": " << mex(v) << endl;
  }

  // pair<int, int> mn = {maxn, maxn};
  // for (int i = N/2; i >= 1; i--) {
  //   for (int k = 1000; k >= 1; k--) {
  //     if (period(i, k)) {
  //       P[i] = k;
  //       cout << "period " << i << ' ' << k << endl;
  //       ckmin(mn, {k, i});
  //     }
  //   }
  // }
  // cout << mn << endl;
}
