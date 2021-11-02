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

const int maxn = 1e5+5;
int n, q;
ll A[maxn];

namespace Segtree {
  struct Segment {
    ll a, b, net;
    Segment() : a(0), b(0), net(0) {}
    Segment(ll _a, ll _b, ll _net) : a(_a), b(_b), net(_net) {}
  };

  Segment merge(Segment x, Segment y) {
    ll ap = x.a - x.net;
    ll bp = x.b + x.net;

    ll a = x.a;
    ll b = x.b;
    if (y.a > ap) a += y.a - ap;
    if (y.b > bp) b += y.b - bp;

    return Segment(a, b, x.net + y.net);
  }

  struct Node {
    int s, e, m;
    //covers s,e;
    Segment seg;
    Node *l, *r;
    
    Node(int a, int b) {
      s = a;
      e = b;
      if (s != e) {
        m = (s+e)/2;
        l = new Node(s,m);
        r = new Node(m+1,e);
        seg = merge(l->seg, r->seg);
      }
      else {
        if (A[s] < 0) 
          seg = Segment(0, A[s], A[s]);
        else if (A[s] > 0) 
          seg = Segment(A[s], 0, A[s]);
        else
          seg = Segment();
        l = NULL;
        r = NULL;
      }
    }

    Segment get_segment(int st, int en) {
      if (st <= s && e <= en) {
        return seg;
      }
      Segment ret = Segment();
      if (st <= m) {
        ret = merge(l->get_segment(st,en),ret);
      }
      if (en > m) {
        ret = merge(ret,r->get_segment(st,en));
      }
      return ret;
    }

    ll get_ans(int st, int en) {
      Segment q = get_segment(st, en);
      if (q.net == 0 && q.a == 0) return q.b;
      else return -1;
    }
  };
}
using Seg = Segtree::Node;


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> q;
  FOR(i, 1, n+1) cin >> A[i];
  FOR(i, 1, n+1) {
    ll bi; cin >> bi;
    A[i] -= bi;
  }

  Seg root = Seg(1, n);
  
  while (q--) {
    int l, r; cin >> l >> r;
    cout << root.get_ans(l, r) << '\n';
  }
}
