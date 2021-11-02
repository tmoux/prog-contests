#include <bits/stdc++.h>
 
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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
// template<typename U, typename T>
// ostream& operator<<(ostream& o, const U<T>& v) {
//   o << "[";
//   for (auto it = v.begin(); it != v.end(); ++it) {
//     o << *it; if (next(it) != v.end()) o << ", ";
//   }
//   o << "]";
//   return o;
// }

const int MOD = 1e9+7;

struct DSU {
  set<int> roots;
  vector<int> parent;
  vector<int> L;
  int n;

  int getpar(int i) {
    return parent[i] < 0 ? i : parent[i] = getpar(parent[i]);
  }

  DSU(int _n) {
    n = _n;
    parent = vector<int>(n, -1);
    L.resize(n);
    F0R(i, n) {
      roots.insert(i);
      L[i] = i;
    }
  }

  void merge(int a, int b) {
    a = getpar(a);
    b = getpar(b);
    if (a == b) return;

    if (-parent[a] < -parent[b]) swap(a, b);
    parent[a] += parent[b];
    parent[b] = a;
    if (roots.count(b)) roots.erase(b);
    L[a] = min(L[a], L[b]);
  }

  ll mergeRange(int a, int b) {
    a = getpar(a);
    b = getpar(b);
    if (a > b) swap(a, b);
    if (a < b) {
      ll cnt = 0;

      vector<int> toMerge;
      for (auto it = roots.find(a); it != roots.end() && L[*it] <= b; ++it) {
        cnt += 1LL * (-parent[*it]) * (L[*it] - a);

        toMerge.push_back(*it);
      }

      for (int i: toMerge) {
        merge(a, i);
      }

      return cnt;
    }
    else return 0;
  }
};

const ll INV = -1; //invalid number for lazy

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
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

	ll getsum(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		ll ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

ll solve() {
  int N, M; cin >> N >> M;

  ll ans = 1;
  ll total = 1LL*N*(N-1)/2;

  Node root = Node(0, N-1);
  F0R(i, N) {
    root.add(i,i,i);
  }
  while (M--) {
    int a, b; cin >> a >> b;
    a--; b--;

    if (a > b) swap(a, b);
    while (a != root.getsum(a,a)) a = root.getsum(a,a);
    if (a < root.getsum(b,b)) {
      int r = a;
      for (int k = 20; k >= 0; k--) {
        int nr = r + (1<<k);
        if (nr < N && root.getsum(nr,nr) <= b) {
          r = nr;
        }
      }

      ll sum = root.getsum(a, r) - 1LL * (r - a + 1) * a;
      total += sum;

      root.add(a, r, a);
    }

    //cout << "total " << total << endl;
    ans = (ans * total) % MOD;
  }

  return ans;

  /*
  DSU dsu(N);
  while (M--) {
    int a, b; cin >> a >> b;
    a--; b--;

    total += dsu.mergeRange(a, b);
    //cout << "total " << total << endl;
    ans = (ans * total) % MOD;
  }

  return ans;
  */

  /*
  vector<int> L(N);
  F0R(i, N) L[i] = i;

  ll ans = 1;
  ll total = 1LL*N*(N-1)/2;
  while (M--) {
    int a, b; cin >> a >> b;
    a--; b--;
    if (a > b) swap(a, b);
    while (a != L[a]) a = L[a];
    if (a < L[b]) {
      for (int i = a; i < N && L[i] <= b; i++) {
        int add = L[i] - a;
        total += add;
        L[i] = a;
      }
    }
    cout << M << ' ' << total << '\n';

    ans = (ans * total) % MOD;
  }
  return ans;
  */
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
