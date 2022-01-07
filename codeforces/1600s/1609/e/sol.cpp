#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

vector<array<int,3>> merges;
string sub[] = {"a", "b", "c", "ab", "bc"};
void precalc() {
  auto has_subsequence = [&](string_view s, string t) -> bool {
    int pt = 0;
    for (char c: s) {
      if (pt < sz(t) && c == t[pt]) pt++;
    }
    return pt >= sz(t);
  };
  for (int mask1 = 0; mask1 < (1<<5); mask1++) {
    for (int mask2 = 0; mask2 < (1<<5); mask2++) {
      vector<string> checks;
      for (int j = 0; j < 5; j++) {
        if (mask1 & (1<<j)) {
          checks.push_back(sub[j]);
          for (int k = 0; k < 5; k++) {
            if (mask2 & (1<<k)) {
              checks.push_back(sub[k]);
              checks.push_back(sub[j] + sub[k]);
            }
          }
        }
      }
      if (!any_of(all(checks), [&](string s){return has_subsequence(s, "abc");})) {
        int newmask = 0;
        for (string s: checks) {
          for (int j = 0; j < 5; j++) {
            if (has_subsequence(s, sub[j])) {
              newmask |= (1<<j);
            }
          }
        }
        merges.push_back({mask1, mask2, newmask});
      }
    }
  }
}

string S;

struct Segment {
  int dp[1<<5];
  Segment() {
    memset(dp, 0, sizeof dp);
  }
  Segment(char c) {
    for (int mask = 0; mask < (1<<5); mask++) dp[mask] = 1e9;
    int x = c-'a';
    for (int j = 0; j < 3; j++) {
      if (j == x) dp[1<<j] = 0;
      else dp[1<<j] = 1;
    }
  }

  void merge(Segment a, Segment b) {
    for (int mask = 0; mask < (1<<5); mask++) {
      dp[mask] = 1e9;
    }
    for (auto [mask1, mask2, newmask]: merges) {
      ckmin(dp[newmask], a.dp[mask1] + b.dp[mask2]);
    }
  }
};

struct Node {
	int s, e, m;
	//covers s,e;
	Segment sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
      sum.merge(l->sum, r->sum);
		}
		else {
      sum = Segment(S[s]);
			l = nullptr;
			r = nullptr;
		}
	}

	void add(int i, char c) {
		if (s == e) {
      sum = Segment(c);
			return;
		}
		if (i <= m) {
			l->add(i,c);
		}
		else if (i > m) {
			r->add(i,c);
		}
		else assert(false);
    sum.merge(l->sum, r->sum);
	}
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  precalc();

  int n, q; cin >> n >> q;
  cin >> S;

  Node *root = new Node(0, n-1);
  REP(q) {
    int i; char c; 
    cin >> i >> c; i--;
    root->add(i, c);
    int ans = n;
    for (int mask = 0; mask < (1<<5); mask++) {
      ckmin(ans, root->sum.dp[mask]);
    }
    cout << ans << '\n';
  }
}
