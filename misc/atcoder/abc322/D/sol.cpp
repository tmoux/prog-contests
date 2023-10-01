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

using vpi = vector<array<int, 2>>;
const int MX = 4;

bool A[MX][MX];

bool valid(int i, int j, const vpi& v)  { // fill in as well
  for (auto [x, y]: v) {
    int nx = i + x, ny = j + y;
    if (!(0 <= nx && nx < MX && 0 <= ny && ny < MX) || A[nx][ny]) return false;
    else A[nx][ny] = 1;
  }
  return true;
}

vpi rotate(vpi v) {
  F0R(i, sz(v)) {
    int x = v[i][0], y = v[i][1];
    v[i][0] = y, v[i][1] = 3 - x;
  }
  return v;
}

vpi normalize(vpi v) {
  sort(all(v));
  int x = v[0][0], y = v[0][1];
  F0R(i, sz(v)) {
    v[i][0] -= x;
    v[i][1] -= y;
  }
  return v;
}

array<int, 2> findNext() {
  F0R(i, MX) {
    F0R(j, MX) {
      if (!A[i][j]) return {i, j};
    }
  }
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  vector<vpi> polys;
  int total = 0;
  REP(3) {
    vpi v;
    F0R(i, 4) {
      string s; cin >> s;
      F0R(j, 4) {
        if (s[j] == '#') {
          v.push_back({i, j});
          total++;
        }
      }
    }
    polys.push_back(v);
  }

  if (total != MX * MX) {
    cout << "No" << '\n';
    return 0;
  }

  vector<vector<vpi>> Ps(3);
  F0R(i, 3) {
    auto v = polys[i];
    REP(4) {
      Ps[i].push_back(normalize(v));
      v = rotate(v);
    }
  }

  for (auto p0: Ps[0]) {
    for (auto p1: Ps[1]) {
      for (auto p2: Ps[2]) {
        array<vpi, 3> pieces = {p0, p1, p2};
        vector<int> p = {0, 1, 2};
        do {
          memset(A, 0, sizeof A);
          bool poss = true;
          F0R(i, 3) {
            auto v = pieces[p[i]];
            auto [x, y] = findNext();
            if (valid(x, y, v)) {

            }
            else {
              poss = false;
              break;
            }
          }

          if (poss) {
            cout << "Yes" << '\n';
            // cout << p0 << endl;
            // cout << p1 << endl;
            // cout << p2 << endl;
            // F0R(i, 4) {
            //   F0R(j, 4) {
            //     cout << A[i][j] << ' ';
            //   }
            //   cout << endl;
            // }
            return 0;
          }
        } while (next_permutation(all(p)));
      }
    }
  }

  cout << "No" << '\n';
}
