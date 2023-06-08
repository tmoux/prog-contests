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

int p[10000], A[10000];
int N;

// int ask1(int i) {
//   cout << "? ";
//   FOR(j, 1, N+1) {
//     cout << (j == i ? 2 : 1) << ' ';
//     A[j] = (p[j] + (j == i ? 2 : 1));
//   }
//   cout << endl;
//
//   FOR(j, 1, N+1) {
//     FOR(k, j+1, N+1) {
//       if (A[j] == A[k]) return j;
//     }
//   }
//   return 0;
// }
//
// int ask2(int i) {
//   cout << "? ";
//   FOR(j, 1, N+1) {
//     cout << (j == i ? 1 : 2) << ' ';
//     A[j] = (p[j] + (j == i ? 1 : 2));
//   }
//   cout << endl;
//   FOR(j, 1, N+1) {
//     FOR(k, j+1, N+1) {
//       if (A[j] == A[k]) return j;
//     }
//   }
//   return 0;
// }


int ask1(int i) {
  cout << "? ";
  FOR(j, 1, N+1) {
    cout << (j == i ? 2 : 1) << ' ';
  }
  cout << endl;
  // FOR(j, 1, N+1) {
  //   cout << (p[j] + (j == i ? 2 : 1)) << ' ';
  // }
  // cout << endl;
  int k; cin >> k;
  return k;
}

int ask2(int i) {
  cout << "? ";
  FOR(j, 1, N+1) {
    cout << (j == i ? 1 : 2) << ' ';
  }
  cout << endl;
  // FOR(j, 1, N+1) {
  //   cout << (p[j] + (j == i ? 1 : 2)) << ' ';
  // }
  // cout << endl;
  int k; cin >> k;
  return k;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  // FOR(i, 1, N+1) cin >> p[i];
  vector<int> nxt(N+1), cnt(N+1);
  FOR(i, 1, N+1) {
    int k = ask1(i);
    if (!k) continue;
    if (k < i) {
      nxt[i] = k;
      cnt[k]++;
    }
  }
  FOR(i, 1, N+1) {
    int k = ask2(i);
    if (!k) continue;
    if (k < i) {
      nxt[k] = i;
      cnt[i]++;
    }
  }
  int s = -1;
  // cout << nxt << ' ' << cnt << endl;
  FOR(i, 1, N+1) if (!cnt[i]) s = i;
  assert(s != -1);

  vector<int> ans(N+1);
  int c = 1;
  while (1) {
    ans[s] = c++;
    if (!nxt[s]) break;
    s = nxt[s];
  }
  cout << "! ";
  FOR(i, 1, N+1) {
    cout << ans[i] << ' ';
  }
  cout << endl;
}
