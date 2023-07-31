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


int X, Y;
int cx = -1, cy = -1;
string found, closer, further, same, notfound;
int Q = 0;

const int MX = 1000000;
string CLOSER, FURTHER;
string query(int x, int y) {
  Q++; assert(Q <= 64);
  cout << x << ' ' << y << endl;
  string s;
  getline(cin, s);

  if (s.back() == '!') {
    exit(0);
  }
  return s;
}

void bsearch(int xmin, int xmax, int ymin, int ymax) {
  if (xmin == xmax && ymin == ymax) {
    query(xmin, ymin);
    return;
  }

  int new_xmin = xmin;
  int new_xmax = xmax;
  int new_ymin = ymin;
  int new_ymax = ymax;

  if (xmin < xmax) {
    string B = query(xmax, ymin);
    if (B == CLOSER) {
      new_xmin = (xmin + xmax) / 2 + 1;
    }
    else if (B == FURTHER) {
      new_xmax = (xmin + xmax - 1) / 2;
    }
    else { // equal
      assert((xmin + xmax) % 2 == 0);
      int mid = (xmin + xmax) / 2;
      new_xmin = new_xmax = mid;
    }
  }

  if (ymin < ymax) {
    string D = query(xmax, ymax);
    if (D == CLOSER) {
      new_ymin = (ymin + ymax) / 2 + 1;
    }
    else if (D == FURTHER) {
      new_ymax = (ymin + ymax - 1) / 2;
    }
    else { // equal
      assert((ymin + ymax) % 2 == 0);
      int mid = (ymin + ymax) / 2;
      new_ymin = new_ymax = mid;
    }
  }
  query(new_xmin, new_ymin);
  bsearch(new_xmin, new_xmax, new_ymin, new_ymax);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  string not_found = query(1, 0);
  string x1 = query(0, 0);
  string y2 = query(0, 1);
  string y1 = query(0, 0);

  if (x1 == y1) {
    FURTHER = x1;
    CLOSER = y2;
    bsearch(0, MX, 0, MX);
  }
  else {
    // on x or y-axis
    // check corners first
    // total: 8 + 40 queries
    query(0, MX);
    query(MX, 0);
    query(MX, MX);
    CLOSER = query(MX, MX-1);

    if (CLOSER == y2) {
      FURTHER = y1;
      query(0, 0);
      bsearch(0, 0, 1, MX-1);
    }
    else {
      assert(CLOSER == y1);
      FURTHER = y2;
      query(0, 0);
      bsearch(1, MX-1, 0, 0);
    }
  }
}
