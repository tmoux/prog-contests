#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define int ll
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

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
// }}}


struct Ins {
  string ins;
  string x, v;

  string to_string() {
    return ins + " " + x + " " + v;
  }
};

void run_instructions(vector<int> inputs, vector<Ins> vec) {
  cout << inputs << endl;
  int pt = 0;
  int w, x, y, z;
  w = x = y = z = 0;
  for (auto [ins, var, v]: vec) {
    if (ins == "inp") {

      w = inputs[pt++];

      printf("w: %lld\nx: %lld\ny: %lld\nz: %lld\n\n", w, x, y, z);
      //cout << z % 26 << endl;
    }
    else {
      int* r;
      if (var == "x") r = &x;
      else if (var == "y") r = &y;
      else if (var == "z") r = &z;
      else {
        cout << var << endl;
        assert(false);
      }

      int val;
      if (v[0] == 'w') val = w;
      else if (v[0] == 'x') val = x;
      else if (v[0] == 'y') val = y;
      else if (v[0] == 'z') val = z;
      else val = stoi(v);


      if (ins == "add") {
          *r += val;
      }
      else if (ins == "mul") {
          *r *= val;
      }
      else if (ins == "div") {
          //cout << "dividing by " << val << endl;
          //cout << *r << ' ';
          *r /= val;
          //cout << *r << '\n';
      }
      else if (ins == "mod") {
          *r %= val;
      }
      else if (ins == "eql") {
          *r = (*r == val ? 1 : 0);
          cout << "equal " << *r << endl;
      }
    }
    //printf("w: %lld\nx: %lld\ny: %lld\nz: %lld\n\n", w, x, y, z);
    //cout << t++ << endl;
  }
  if (z == 0) {
    cout << "Found it" << endl;
    cout << inputs << endl;
  }
  assert(z != 0);
}

int32_t main() {
  string ins;
  string var, v;
  vector<Ins> vec;
  while (cin >> ins) {
    // if (t > 18) break;
    if (ins == "inp") {
      cin >> var;
      vec.push_back({ins, var, ""});
    }
    else {
      cin >> var >> v;
      vec.push_back({ins, var, v});
    }
  }

  vector<int> inputs = {
    9,
    1,
    8,
    1,
    9,
    8,
    3,
    1,
    2,
    9,
    8,
    3,
    3,
    5,
  };
  /*
  F0R(a8, 10) {
  F0R(a9, 10) {
  F0R(a10, 10) {
  F0R(a11, 10) {
  F0R(a12, 10) {
  F0R(a13, 10) {
    inputs[8] = a8;
    inputs[9] = a9;
    inputs[10] = a10;
    inputs[11] = a11;
    inputs[12] = a12;
    inputs[13] = a13;
    run_instructions(inputs, vec);
  }}}}}}
  */

  run_instructions(inputs, vec);

  //printf("w: %lld\nx: %lld\ny: %lld\nz: %lld\n\n", w, x, y, z);

  int n = 14;
  F0R(i, n) {
    cout << setw(3) << inputs[i] << ' ';
  }
  cout << endl;
  for(int j: {5, 15}) {
    F0R(i, n) {
      cout << setw(3) << vec[i*18+j].v << ' ';
    }
    cout << '\n';
  }
}
