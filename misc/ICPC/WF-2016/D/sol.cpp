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

array<int, 2> pos[] = {
{0, 1},
{1, 0},
{1, 3},
{3, 1},
{4, 0},
{4, 3},
{6, 1}
};
array<int, 2> pos2[] = {
{0, 2},
{2, 0},
{2, 3},
{3, 2},
{5, 0},
{5, 3},
{6, 2}
};
int COL[] = {0, 5, 12, 17};

array<int, 7> digits[] = {
{1, 1, 1, 0, 1, 1, 1},
{0, 0, 1, 0, 0, 1, 0},
{1, 0, 1, 1, 1, 0, 1},
{1, 0, 1, 1, 0, 1, 1},
{0, 1, 1, 1, 0, 1, 0},
{1, 1, 0, 1, 0, 1, 1},
{1, 1, 0, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 1, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 0, 1, 1},
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<array<int, 30>> A(N);
  vector<string> g(7);
  F0R(i, N) {
    F0R(j, 7) {
      cin >> g[j];
    }
    int cnt = 0;
    F0R(j, 4) {
      F0R(k, 7) {
        A[i][cnt++] = g[pos[k][0]][COL[j] + pos[k][1]] == 'X';
      }
    }
    A[i][cnt++] = g[2][10] == 'X';
    A[i][cnt++] = g[4][10] == 'X';
  }
  array<int, 30> which;
  F0R(d, 30) {
    int a = 0, b = 0;
    F0R(i, N) {
      if (A[i][d] == 0) a++;
      else b++;
    }
    if (a == 0) which[d] = 1;
    else if (b == 0) which[d] = 0;
    else which[d] = 2;
  }

  vector<array<int, 30>> V;
  for (int hour = 0; hour < 24; hour++) {
    for (int min = 0; min < 60; min++) {
      array<int, 30> a; F0R(d, 30) a[d] = 0;
      int cnt = 0;
      if (hour/10 > 0) F0R(i, 7) a[cnt++] = digits[hour/10][i];
      else cnt += 7;
      F0R(i, 7) a[cnt++] = digits[hour%10][i];
      F0R(i, 7) a[cnt++] = digits[min/10][i];
      F0R(i, 7) a[cnt++] = digits[min%10][i];
      a[cnt++] = 1;
      a[cnt++] = 1;
      V.push_back(a);
    }
  }

  array<char, 30> ans; F0R(d, 30) ans[d] = '#';
  int cnt = 0;
  F0R(i, sz(V)) {
    bool poss = true;
    array<char, 30> tr;
    F0R(d, 30) {
      if (which[d] == 0) {
        bool matches = 1;
        F0R(j, N) {
          if (A[j][d] != V[(i+j)%sz(V)][d]) {
            matches = false;
            break;
          }
        }
        tr[d] = matches ? '?' : '0';
      }
      else if (which[d] == 1) {
        bool matches = 1;
        F0R(j, N) {
          if (A[j][d] != V[(i+j)%sz(V)][d]) {
            matches = false;
            break;
          }
        }
        tr[d] = matches ? '?' : '1';
      }
      else if (which[d] == 2) {
        tr[d] = 'W';
        F0R(j, N) {
          if (A[j][d] != V[(i+j)%sz(V)][d]) {
            poss = false;
            break;
          }
        }
      }
      else assert(false);
    }
    if (poss) {
      cnt++;
      F0R(d, 30) {
        if (ans[d] == '?') continue;
        else ans[d] = tr[d];
      }
    }
  }
  if (cnt > 0) {
    vector<string> OUT(7, string(21, '.'));
    int c = 0;
    F0R(j, 4) {
      F0R(k, 7) {
        OUT[pos[k][0]][COL[j] + pos[k][1]] = ans[c];
        OUT[pos2[k][0]][COL[j] + pos2[k][1]] = ans[c];
        c++;
      }
    }
    OUT[2][10] = ans[c++];
    OUT[4][10] = ans[c++];
    for (auto s: OUT) {
      cout << s << '\n';
    }
  }
  else cout << "impossible\n";
}
