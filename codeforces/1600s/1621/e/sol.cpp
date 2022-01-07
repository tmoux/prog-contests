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

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		mini = 0;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void add(int i, int x) {
		if (s == e) {
			sum += x;
			mini = sum;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		sum = l->sum + r->sum;
		mini = min(l->mini,r->mini);
	}

	int getmini(int st, int en) {
    if (st > en || e < st || s > en) return 1;
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = 1;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}	

	int getsum(int st, int en) {
		if (st <= s && e <= en) {
			return sum;
		}
		int ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

struct Rational {
  ll a, b;
  Rational(ll _a, ll _b) : a(_a), b(_b) {}

  bool operator<(const Rational& rhs) const {
    return a * rhs.b < b * rhs.a;
  }
  bool operator<=(const Rational& rhs) const {
    return a * rhs.b <= b * rhs.a;
  }
  bool operator<=(int rhs) const {
    return *this <= Rational(rhs, 1);
  }
};

void solve() {
  int n, m; cin >> n >> m;
  vector<ll> teachers(n);
  for (auto& i: teachers) cin >> i;
  vector<vector<ll>> students(m);
  vector<ll> sum(m);
  F0R(i, m) {
    int k; cin >> k;
    REP(k) {
      int b; cin >> b;
      sum[i] += b;
      students[i].push_back(b);
    }
  }

  sort(all(teachers), greater<int>());
  vector<pair<Rational,int>> averages;
  F0R(i, m) {
    averages.push_back({Rational(sum[i], sz(students[i])), i});
  }
  sort(all(averages), greater<pair<Rational,int>>());

  vector<int> id(m);
  F0R(i, m) {
    id[averages[i].second] = i;
  }

  Node *normal = new Node(0, m-1);
  F0R(i, m) {
    if (averages[i].first <= teachers[i]) {
      normal->add(i, 1);
    }
  }
  Node *shift_left = new Node(0, m-1);
  F0R(i, m) {
    if (i == 0 || averages[i].first <= teachers[i-1]) {
      shift_left->add(i, 1);
    }
  }
  Node *shift_right = new Node(0, m-1);
  F0R(i, m) {
    if (i == m-1 || averages[i].first <= teachers[i+1]) {
      shift_right->add(i, 1);
    }
  }

  /*
  F0R(i, m) {
    cout << normal->getmini(i, i) << ' ';
  }
  cout << '\n';
  */

  //cout << averages << endl;


  vector<bool> ans;
  F0R(i, m) {
    Rational avg = Rational(sum[i], sz(students[i]));
    for (int j: students[i]) {
      Rational new_avg = Rational(sum[i]-j, sz(students[i])-1);
      int x = id[i];
      int y = distance(averages.begin(), upper_bound(all(averages), make_pair(new_avg, 0), greater<pair<Rational,int>>()));

      bool poss = true;
      //cout << avg << ' ' << new_avg << endl;
      //cout << x << ' ' << y << endl;
      //cout << endl;
      if (new_avg <= avg) {
        assert(x <= y);
        poss &= normal->getmini(0, x-1) > 0;
        poss &= normal->getmini(y, m-1) > 0;
        poss &= shift_left->getmini(x+1, y-1) > 0;
        poss &= new_avg <= teachers[y-1];
      }
      else {
        assert(y <= x);
        poss &= normal->getmini(0, y-1) > 0;
        poss &= normal->getmini(x+1, m-1) > 0;
        poss &= shift_right->getmini(y, x-1) > 0;
        poss &= new_avg <= teachers[y];
      }

      ans.push_back(poss);
    }
  }
  //output
  for (auto b: ans) {
    cout << b;
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}
