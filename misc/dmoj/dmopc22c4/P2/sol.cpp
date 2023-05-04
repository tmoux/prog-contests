#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define int ll

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

// try all 4 flips (id, R, C, RC)

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<vector<int>> A(N, vector<int>(M));
  vector<vector<int>> B(N, vector<int>(M));
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j];
    }
  }
  F0R(i, N) {
    F0R(j, M) {
      cin >> B[i][j];
    }
  }

  auto flipR = [&](vector<vector<int>> B) {
    F0R(i, N) {
      if (i < N-1-i) {
        F0R(j, M) {
          swap(B[i][j], B[N-1-i][j]);
        }
      }
    }
    return B;
  };

  auto flipC = [&](vector<vector<int>> B) {
    F0R(j, M) {
      if (j < M-1-j) {
        F0R(i, N) {
          swap(B[i][j], B[i][M-1-j]);
        }
      }
    }
    return B;
  };

  auto check = [&](vector<vector<int>> B, int parity) -> bool {
    vector<array<int, 3>> diffs;
    F0R(i, N) {
      F0R(j, M) {
        B[i][j] -= A[i][j];
      }
    }
    // cout << B << endl;

    F0R(i, N) {
      F0R(j, M) {
        if (i == N-i-1 && j == M-j-1) {
          if (abs(B[i][j]) % 2 != 0) return false;
        }
        else if (i == N-1-i) {
          if (abs(B[i][j] - B[i][M-j-1]) % 2 != 0) return false;
        }
        else if (j == M-j-1) {
          if (abs(B[i][j] - B[N-i-1][j]) % 2 != 0) return false;
        }
        int a = B[i][j];
        int b = B[N-i-1][j];
        int c = B[i][M-j-1];
        int d = B[N-i-1][M-j-1];

        if (a + d != b + c) return false;
      }
    }
    return true;
  };

  if (check(B, 0)) {
    cout << "YES\n";
    return 0;
  }

  B = flipR(B);
  if (check(B, 1)) {
    cout << "YES\n";
    return 0;
  }

  B = flipC(B);
  if (check(B, 0)) {
    cout << "YES\n";
    return 0;
  }

  B = flipR(B);
  if (check(B, 1)) {
    cout << "YES\n";
    return 0;
  }

  cout << "NO\n";
}
