#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(2);
// }}}

void solve() {
  using ull = unsigned long long;
  int N, M; cin >> N >> M;
  vector<ull> H(N);
  ull ALL = 0;
  F0R(i, N) {
    H[i] = rng();
    ALL ^= H[i];
  }
  vector<vector<int>> A(N, vector<int>(M));
  vector<vector<int>> B(N, vector<int>(M));
  F0R(i, N) F0R(j, M) {
    cin >> A[i][j];
    B[i][M-1-j] = A[i][j];
  }

  vector<vector<ull>> hashes(M);
  {
    vector<int> mn(N, 1e9), mx(N, -1e9);
    set<int> S;
    set<pair<int, int>> T; // R, id
    F0R(i, N) F0R(j, M) S.insert(A[i][j]);
    F0R(j, M-1) {
      F0R(i, N) {
        if (T.count({mx[i], i})) T.erase({mx[i], i});
        ckmin(mn[i], B[i][j]);
        ckmax(mx[i], B[i][j]);
        T.insert({mx[i], i});
        for (auto it = S.lower_bound(mn[i]); it != S.end() && *it < mx[i];) {
          S.erase(it++);
        }
      }

      ull curHash = 0;
      for (auto it = T.begin(); it != T.end(); ++it) {
        auto [r, id] = *it;
        curHash ^= H[id];
        if (next(it) == T.end() || next(it)->first > r) {
          if (S.count(r)) {
            hashes[M-2-j].push_back(curHash);
          }
        }
      }
      sort(all(hashes[M-2-j]));
      // cout << j << ": " << hashes[M-2-j] << endl;
    }
  }

  {
    vector<int> mn(N, 1e9), mx(N, -1e9);
    set<int> S;
    set<pair<int, int>> T;
    F0R(i, N) F0R(j, M) S.insert(A[i][j]);
    F0R(j, M-1) {
      F0R(i, N) {
        if (T.count({mx[i], i})) T.erase({mx[i], i});
        ckmin(mn[i], A[i][j]);
        ckmax(mx[i], A[i][j]);
        T.insert({mx[i], i});
        for (auto it = S.lower_bound(mn[i]); it != S.end() && *it < mx[i];) {
          S.erase(it++);
        }
      }

      ull curHash = ALL;
      vector<bool> rows(N);

      for (auto it = T.begin(); it != T.end(); ++it) {
        auto [r, id] = *it;
        curHash ^= H[id];
        rows[id] = 1;
        if (next(it) == T.end() || next(it)->first > r) {
          if (S.count(r)) {
            if (curHash == 0 || curHash == ALL) continue;
            auto itl = lower_bound(all(hashes[j]), curHash);
            if (itl != hashes[j].end() && *itl == curHash) {
              // FOUND it
              // cout << T << endl;
              // cout << rows << endl;
              cout << "YES\n";
              F0R(i, N) {
                cout << (rows[i] ? 'B' : 'R');
              }
              cout << ' ' << j+1 << '\n';
              return;
            }
          }
        }
      }
    }
  }
  cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
