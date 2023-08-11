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

const int maxn = 1e5+5, maxk = 18;
int N, Q;
int A[maxn];
int jmp[maxk][maxn], cnt[maxk][maxn];

int spf[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
      for (int j = i; j < maxn; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
}

vector<int> primes(int x) {
  vector<int> v;
  while (x > 1) {
    int p = spf[x];
    v.push_back(p);
    while (x % p == 0) x /= p;
  }
  return v;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  cin >> N >> Q;
  F0R(i, N) {
    cin >> A[i];
  }

  map<int, int> last;
  F0Rd(i, N) {
    auto ps = primes(A[i]);
    if (i == N-1) jmp[0][i] = N;
    else {
      if (std::gcd(A[i], A[i+1]) > 1) jmp[0][i] = i+1;
      else {
        jmp[0][i] = jmp[0][i+1];
        for (auto p: ps) {
          if (last.count(p)) {
            ckmin(jmp[0][i], last[p]);
          }
        }
      }
    }
    for (auto p: ps) {
      last[p] = i;
    }
  }
  F0R(i, N) cnt[0][i] = 1;

  for (int k = 1; k < maxk; k++) {
    F0R(i, N) {
      if (jmp[k-1][i] == N) {
        jmp[k][i] = N;
        cnt[k][i] = cnt[k-1][i];
      }
      else {
        jmp[k][i] = jmp[k-1][jmp[k-1][i]];
        cnt[k][i] = cnt[k-1][i] + cnt[k-1][jmp[k-1][i]];
      }
    }
  }

  auto query = [&](int l, int r) {
    int ans = 0;
    F0Rd(k, maxk) {
      int nl = jmp[k][l];
      if (nl <= r+1) {
        ans += cnt[k][l];
        l = nl;
        if (l == N) break;
      }
    }
    if (l <= r) ans++;
    return ans;
  };

  while (Q--) {
    int l, r; cin >> l >> r;
    l--, r--;
    cout << query(l, r) << '\n';
  }
}
