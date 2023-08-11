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
			sum = x;
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
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = 1e9;
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

void solve() {
  int n; cin >> n;
  set<int> s;
  vector<array<int,2>> v(n);
  F0R(i, n) {
    cin >> v[i][0];
    s.insert(v[i][0]);
  }
  F0R(i, n) {
    cin >> v[i][1];
    s.insert(v[i][1]);
  }
  map<int,int> compress;
  int pt = 0;
  for (int x: s) {
    compress[x] = pt++;
  }
  array<int,2> maxPt = {-1, -1};

  map<int, int> xToY, yToX;
  F0R(i, n) {
    v[i][0] = compress[v[i][0]];
    v[i][1] = compress[v[i][1]];

    xToY[v[i][0]] = v[i][1];
    yToX[v[i][1]] = v[i][0];

    ckmax(maxPt, v[i]);
  }
  int INF = pt;
  int minX = maxPt[0], minY = maxPt[1];
  
  Node *segx = new Node(0, INF);
  Node *segy = new Node(0, INF);
  F0R(i, INF+1) {
    segx->add(i, INF);
    segy->add(i, INF);
  }
  F0R(i, n) {
    if (v[i] != maxPt) {
      segx->add(v[i][1], v[i][0]);
      segy->add(v[i][0], v[i][1]);
    }
  }

  while (true) {
    int x = segx->getmini(minY, INF);
    if (x < INF) {
      ckmin(minX, x);

      int y = xToY[x];
      segx->add(y, INF);
      segy->add(x, INF);
    }
    else break;

    int y = segy->getmini(minX, INF);
    if (y < INF) {
      ckmin(minY, y);

      int x = yToX[y];

      segx->add(y, INF);
      segy->add(x, INF);
    }
    else break;
  }

  F0R(i, n) {
    if (v[i][0] < minX && v[i][1] < minY) {
      cout << 0;
    }
    else cout << 1;
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
