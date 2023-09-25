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

template<typename T>
void output_vector(const vector<T>& v) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << (next(it) == v.end() ? '\n' : ' ');
  }
}

template<typename T>
void output_vector(const vector<T>& v, int offset) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << (*it + offset) << (next(it) == v.end() ? '\n' : ' ');
  }
}

// Note that this is equivalent to sorting rows by a certain order of columns in lexicographic order.
// Claim: Repeating a column does nothing.
//

void no() {
  cout << -1 << '\n';
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<vector<int>> A(N, vector<int>(M));
  vector<vector<int>> B(N, vector<int>(M));
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j];
    }
  }

  map<vector<int>, vector<int>> mp;
  F0R(i, N) {
    F0R(j, M) {
      cin >> B[i][j];
    }
  }
  F0Rd(i, N) {
    mp[B[i]].push_back(i);
  }

  vector<int> init(N);
  F0R(i, N) {
    if (mp.count(A[i])) {
      auto& v = mp[A[i]];
      if (v.empty()) no();
      else {
        int x = v.back(); v.pop_back();
        init[x] = i;
      }
    }
    else no();
  }

  vector<int> ops;
  auto valid_op = [&](int j, const vector<vector<int>>& v) -> bool {
    for (const auto& g: v) {
      FOR(i, 1, sz(g)) {
        if (A[g[i-1]][j] > A[g[i]][j]) return false;
      }
    }
    return true;
  };

  auto split = [&](int j, const vector<vector<int>>& v) -> vector<vector<int>> {
    vector<vector<int>> nv;

    vector<vector<int>> vec(N+1);
    for (const auto& g: v) {
      vector<int> xs;
      for (auto i: g) {
        vec[A[i][j]].push_back(i);
        xs.push_back(A[i][j]);
      }

      sort(all(xs)); xs.erase(unique(all(xs)), xs.end());
      for (auto x: xs) {
        if (sz(vec[x]) > 1) {
          nv.push_back(vec[x]);
        }
      }

      for (auto i: g) {
        vec[A[i][j]].clear();
      }
    }
    return nv;
  };

  vector<vector<int>> v = {init};
  vector<int> used_cols(M, false);
  REP(M) {
    bool found = false;
    F0R(j, M) {
      if (used_cols[j]) continue;
      if (valid_op(j, v)) {
        v = split(j, v);
        ops.push_back(j);
        used_cols[j] = 1;
        found = true;
        break;
      }
    }
    if (!found) break;
  }

  bool poss = true;
  for (const auto& g: v) {
    FOR(i, 1, sz(g)) {
      if (g[i-1] > g[i]) {
        poss = false;
        break;
      }
    }
  }
  if (poss) {
    reverse(all(ops));
    cout << sz(ops) << '\n';
    output_vector(ops, +1);
  }
  else {
    cout << -1 << '\n';
  }
}
