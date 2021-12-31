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

struct Cuboid {
  int x1, x2, y1, y2, z1, z2;
};

struct Line {
  int x, y1, y2;
  int open;
  bool operator<(const Line& rhs) const {
    if (x != rhs.x) return x < rhs.x;
    else return open > rhs.open; //do closing ones first
  }
};

struct Rectangle {
  int x1, x2, y1, y2;
};

const int INV = -1; //invalid number for lazy

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int lazy;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = INV;
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

	void push() {
		if (lazy == INV) return;
		if (s != e) {
			l->lazy = lazy;
			l->sum = (l->e - l->s + 1) * lazy;

			r->lazy = lazy;
			r->sum = (r->e - r->s + 1) * lazy;
		}
		lazy = INV;
	}

	void pull() {
		sum = l->sum + r->sum;
	}

	void add(int st, int en, ll x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy = x;
			sum = (e - s + 1) * x;
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		pull();
	}

	int getsum(int st, int en) {
		push();
		//if completely included
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

ll rectangleArea(const vector<Rectangle>& v) {
  vector<Line> lines;
  for (auto [x1, x2, y1, y2]: v) {
    lines.push_back({x1, y1, y2, 1});
    lines.push_back({x2, y1, y2, 0});
  }
  sort(all(lines));
  int i = 0;
  int prev_x = 0;
  Node *seg = new Node(-150000, 150000);
  while (i < sz(lines)) {
    int x = lines[i].x;
    // do closing x
    while (i < sz(lines) && lines[i].x == x && !lines[i].open) {
      i++;
    }

    while (i < sz(lines) && lines[i].x == x && lines[i].open) {
      i++;
    }
    prev_x = x;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  int x1, x2, y1, y2, z1, z2;
  vector<Cuboid> cuboids;
  while (cin >> s >> x1 >> x2 >> y1 >> y2 >> z1 >> z2) {
    if (s == "on") {
      cuboids.push_back({x1, x2, y1, y2, z1, z2});
    }
  }
  reverse(all(cuboids));
  for (Cuboid c: cuboids) {

  }
}
