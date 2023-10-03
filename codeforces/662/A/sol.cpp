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

const int D = 60; //length of masks

ll basis[D]; // basis[i] keeps the mask of the vector whose f value is i

int bs = 0; //basis size

void insertVector(ll mask) {
  if (!mask) return;
	for (int i = 0; i < D; i++) {
		if ((mask & 1ll << i) == 0) continue;

		if (!basis[i]) {
			basis[i] = mask;
			++bs;
			return;
		}

		mask ^= basis[i];
	}
}

int basis_size = 0;
bool inSpan(ll mask) {
	for (int i = 0; i < D; i++) {
		if ((mask & 1ll << i) == 0) continue;
		mask ^= basis[i];
	}
  return mask == 0;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  uint64_t x = 0;
  F0R(i, N) {
    uint64_t a, b; cin >> a >> b;
    x ^= a;
    insertVector(a ^ b);
  }
  if (!inSpan(x)) {
    cout << "1/1" << '\n';
  }
  else {
    int D = bs;
    cout << ((1LL << D) - 1) << "/" << (1LL << D) << '\n';
  }
}
