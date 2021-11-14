#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

// Template {{{
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

template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) requires Container<U<T>>
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

struct Node {/*{{{*/
	int s, e, m;
	//covers s,e;
	int sum;
	int lazy;
	int maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
		maxi = 0;
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
		if (s != e) {
			l->lazy += lazy;
			l->sum += (l->e - l->s + 1) * lazy;
			l->maxi += lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
			r->maxi += lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, int x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
			maxi += x;
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		sum = l->sum + r->sum;
		maxi = max(l->maxi,r->maxi);
	}

	int getmaxi(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return maxi;
		}
		int ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
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
};/*}}}*/

int solve(vector<pair<int,int>> ps, int n) {
  map<int, vector<int>> mp;
  vector<int> belowCount(n, 0);
  for (auto [x, y]: ps) {
    mp[y].push_back(x);
    if (x >= y) belowCount[y]++;
  }

  int below_ptr = 0;
  Node* seg = new Node(0, n);
  for (auto [y, xs]: mp) {
    sort(all(xs));
    while (below_ptr < y) {
      if (below_ptr > 0) seg->add(0, below_ptr-1, belowCount[below_ptr]);
      //cerr << "adding " << belowCount[below_ptr] << '\n';
      below_ptr++;
    }

    /*
    for (int i = 1; i <= 3; i++) {
      cerr << i << ": " << seg->getmaxi(i, i) << endl;
    }
    */

    int dp_val = 0;
    int y_add = 0;
    for (int x: xs) if (x >= y) y_add++;
    for (int x: xs) {
      //cerr << x << ' ' << y << ": " << seg->getmaxi(0, x) + y_add << endl;
      ckmax(dp_val, seg->getmaxi(0, x) + y_add + (x < y ? 1 : 0));
      if (x >= y) y_add--;
    }

    int v = seg->getmaxi(y, y);
    if (dp_val > v) seg->add(y, y, dp_val - v);
  }

  return seg->getmaxi(0, n);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, d; cin >> n >> d;
  vector<pair<int,int>> points;
  set<int> s; s.insert(d);
  map<int, int> compress;
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    if (x >= d) {
      points.push_back({x, y});
      s.insert(x);
      s.insert(y);
    }
  }
  int pt = 0;
  for (int i: s) {
    compress[i] = pt++;
  }
  for (int i = 0; i < sz(points); i++) {
    points[i].first = compress[points[i].first];
    points[i].second = compress[points[i].second];
  }

  int ans = solve(points, pt);
  cout << ans << '\n';
}
