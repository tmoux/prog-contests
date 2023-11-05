#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

struct FenwickTree2D {
  vector<vector<ll>> bit;
  int n, m;

  FenwickTree2D(int _n, int _m) : n(_n), m(_m) {
    bit = vector<vector<ll>>(n, vector<ll>(m));
  }

  ll sum(int x, int y) {
    if (x < 0 || y < 0) return 0LL;
    ll ret = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
        ret += bit[i][j];
    return ret;
  }

  ll recsum(int r1, int r2, int c1, int c2) {
    return sum(r2, c2) - sum(r1-1, c2) - sum(r2, c1-1) + sum(r1-1, c1-1);
  }

  ll get(int x, int y) {
    return recsum(x, x, y, y);
  }

  void add(int x, int y, int delta) {
    for (int i = x; i < n; i = i | (i + 1))
      for (int j = y; j < m; j = j | (j + 1))
        bit[i][j] += delta;
  }

  void clear() {
    F0R(i, n) {
      fill(all(bit[i]), 0);
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M, Q; cin >> N >> M >> Q;
  FenwickTree2D fen(N + M, N + M);

  auto cv1 = [&](int i, int j) -> int { // i -> i + (M-1-j)
    return i + (M - 1 - j);
  };
  auto cv2 = [&](int i, int j) -> int { // j -> j + (N-1-i)
    return j + (N - 1 - i);
  };

  auto update1 = [&](int r, int c, int v) -> void {
    int d = v;
    fen.add(cv1(r, c), c, d);
  };

  auto update2 = [&](int r, int c, int v) -> void {
    int d = v;
    fen.add(r, cv2(r, c), d);
  };

  auto query1 = [&](int r, int c, int h) -> ll {
    int r1 = cv1(r, c);
    ll sum = fen.recsum(r1, r1 + h - 1, c, M-1);

    return sum;
  };

  auto query2 = [&](int r, int c, int h) -> ll {
    int c2 = cv2(r + h - 1, c);
    ll sub = r + h < N ? fen.recsum(r + h, N-1, c2, c2 + h - 1) : 0LL;
    return sub;
  };

  vector<vector<int>> A(N, vector<int>(M));
  vector<vector<int>> init(N, vector<int>(M));
  F0R(i, N) {
    F0R(j, M) {
      cin >> init[i][j];
    }
  }

  vector<bool> isq(Q, false);
  vector<ll> ans(Q);

  vector<array<int, 4>> queries(Q);
  F0R(i, Q) {
    int t, r, c, h; cin >> t >> r >> c >> h;
    if (t == 2) isq[i] = true;
    queries[i] = {t, r, c, h};
  }

  F0R(round, 2) {
    fen.clear();
    F0R(i, N) {
      F0R(j, M) A[i][j] = 0;
    }
    F0R(i, N) {
      F0R(j, M) {
        A[i][j] = init[i][j];
        if (round ==  0) update1(i, j, init[i][j]);
        else update2(i, j, init[i][j]);
      }
    }
    F0R(i, Q) {
      auto [t, r, c, h] = queries[i];
      if (t == 1) {
        int v = h;
        r--, c--;
        int d = v - A[r][c];
        A[r][c] = v;

        if (round == 0) update1(r, c, d);
        else update2(r, c, d);
      }
      else {
        r--, c--;
        r -= h-1;
        if (round == 0) ans[i] += query1(r, c, h);
        else ans[i] -= query2(r, c, h);
      }
    }
  }

  F0R(i, Q) {
    if (isq[i]) {
      cout << ans[i] << '\n';
    }
  }
}
