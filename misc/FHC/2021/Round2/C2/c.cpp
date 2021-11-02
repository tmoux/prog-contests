#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int lazy;
	int mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
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

	void push() {
		if (s != e) {
			l->lazy += lazy;
			l->sum += (l->e - l->s + 1) * lazy;
			l->mini += lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
			r->mini += lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, int x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
			mini += x;
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
		mini = min(l->mini,r->mini);
	}

	int getmini(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = 2e9;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
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
};

template <class K, class V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<K, V, std::less<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
/* order_of_key(k), how many elements <k */
/* find_by_order(k), k'th element (from 0) */
/* both logn */

struct Solver {
  int R, C, K, Rmx;
  vector<vector<char>> grid;

  vector<ordered_set<int>> columns;
  Node* segtree;

  Solver(int _R, int _C, int _K, vector<vector<char>> _grid) {
    R = _R;
    C = _C;
    K = _K;
    Rmx = R + K;
    grid = _grid;

    segtree = new Node(0, Rmx);
    FOR(i, K, Rmx+1) {
      segtree->add(i,i,i-K);
    }

    columns.resize(C);
    F0R(i, R) {
      F0R(j, C) {
        if (grid[i][j] == 'X') {
          addX(i, j);
        }
      }
    }
  }

  void update(int r, int c) {
    if (grid[r][c] == 'X') {
      removeX(r, c);
      grid[r][c] = '.';
    }
    else {
      addX(r, c);
      grid[r][c] = 'X';
    }
  }

  int get_kth(int c) {
    auto it = columns[c].find_by_order(K);
    if (it == columns[c].end()) return -1;
    else return *it;
  }

  void addX(int r, int c) {
    //cout << "adding " << r << ' ' << c << '\n';
    int kth = get_kth(c);
    if (kth != -1) {
      segtree->add(kth, Rmx, -1);
    }
    columns[c].insert(r);

    int new_kth = get_kth(c);

    if (new_kth != -1) {
      segtree->add(new_kth, Rmx, 1);
    }
    if (new_kth == -1 || r < new_kth) {
      segtree->add(r, r, 1);
    }
  }

  void removeX(int r, int c) {
    int kth = get_kth(c);
    if (kth != -1) {
      segtree->add(kth, Rmx, -1);
    }

    columns[c].erase(r);

    if (kth == -1 || r < kth) {
      segtree->add(r, r, -1);
    }

    int new_kth = get_kth(c);
    if (new_kth != -1) {
      segtree->add(new_kth, Rmx, 1);
    }
  }

  int get_min() {
    return segtree->getmini(K, Rmx);
  }
};

ll solve() {
  int R, C, K, S; cin >> R >> C >> K >> S;
  K--;
  vector<vector<char>> grid(R, vector<char>(C));
  F0R(i, R) {
    F0R(j, C) {
      cin >> grid[i][j];
    }
  }

  Solver up = Solver(R, C, K, grid);
  reverse(all(grid));
  Solver down(R, C, R-1-K, grid);

  /*
  cout << up.get_min() << endl;
  FOR(i, K, R+K) {
    cout << i << ": " << up.segtree->getsum(i,i) << '\n';
  }
  return 0;
  */
  
  ll answer = 0;
  F0R(i, S) {
    int r, c; cin >> r >> c;
    r--; c--;

    up.update(r, c);
    down.update(R-1-r, c);

    /*
    cout << up.get_min() << endl;
    FOR(i, K, R+K) {
      cout << i << ": " << up.segtree->getsum(i,i) << '\n';
    }
    */

    int ans = min(up.get_min(), down.get_min());
    //cout << r+1 << ' ' << c+1 << ": " << up.get_min() << ' ' << down.get_min() << endl;
    //cout << ans << ' ';
    answer += ans;
  }

  return answer;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
