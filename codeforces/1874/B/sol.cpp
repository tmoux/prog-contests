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

// (a, b, m) -> 8 options, map to 5 states
// do BFS from valid ending states

const int MX = 4e5+5;
bool good[MX];
vector<int> adj[MX];
int dist[MX];

array<int, 8> unpack(int x) {
  array<int, 8> a;
  for (int i = 8-1; i >= 0; i--) {
    a[i] = x % 5;
    x /= 5;
  }
  return a;
}

int pack(array<int, 8> a) {
  int x = 0;
  F0R(i, 8) {
    x = (x * 5) + a[i];
  }
  return x;
}

array<int, 3> unpackBit(int x) {
  return {(x >> 2) & 1, (x >> 1) & 1, x & 1};
};
int packBit(array<int, 3> a) {
  return 4 * a[0] + 2 * a[1] + a[2];
}

array<int, 3> trans(int a, int b, int m, int t) {
  if (t == 0) {
    return {a & b, b, m};
  }
  else if (t == 1) {
    return {a | b, b, m};
  }
  else if (t == 2) {
    return {a, a ^ b, m};
  }
  else if (t == 3) {
    return {a, b ^ m, m};
  }
  else assert(0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int mx = 1;
  REP(8) mx *= 5;
  F0R(x, mx) {
    auto A = unpack(x);

    good[x] = true;
    F0R(i, 8) {
      if (A[i] == 4) continue;
      auto [a, b, m] = unpackBit(i);
      int c = (A[i] >> 1) & 1, d = A[i] & 1;
      if (a != c || b != d) good[x] = false;
    }

    F0R(t, 4) {
      bool poss = true;
      array<int, 8> B = {4, 4, 4, 4, 4, 4, 4, 4};
      F0R(i, 8) {
        if (A[i] == 4) continue;
        auto [a, b, m] = unpackBit(i);

        int j = packBit(trans(a, b, m, t));
        if (B[j] != 4 && B[j] != A[i]) {
          poss = false;
          break;
        }
        else B[j] = A[i];
      }

      if (poss) {
        adj[pack(B)].push_back(x);
      }
    }
  }
  memset(dist, -1, sizeof dist);
  queue<int> q;
  F0R(x, mx) if (good[x]) {
    dist[x] = 0;
    q.push(x);
  }
  while (!q.empty()) {
    auto x = q.front(); q.pop();
    for (auto y: adj[x]) {
      if (dist[y] == -1) {
        dist[y] = dist[x] + 1;
        q.push(y);
      }
    }
  }

  int T; cin >> T;
  REP(T) {
    int A, B, C, D, M; cin >> A >> B >> C >> D >> M;
    array<int, 8> arr = {4, 4, 4, 4, 4, 4, 4, 4};
    bool poss = true;
    F0R(i, 30) {
      int a = (A >> i) & 1;
      int b = (B >> i) & 1;
      int c = (C >> i) & 1;
      int d = (D >> i) & 1;
      int m = (M >> i) & 1;

      int x = packBit({a, b, m});
      int y = (2 * c) + d;
      if (arr[x] != 4 && arr[x] != y) {
        poss = false;
      }
      else {
        arr[x] = y;
      }
    }
    if (!poss) {
      cout << -1 << '\n';
    }
    else {
      cout << dist[pack(arr)] << '\n';
    }
  }
}
