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

/* Waiting for c++20 on cf...
template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};
*/

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) //requires Container<U<T>>
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

namespace Segtree {
  template<typename T> 
  T merge_segment(T a, T b);

  /*
  template<typename T>
  concept Segment = requires(T a, T b) {
    { merge_segment<T>(a, b) } -> std::same_as<T>;
  };
  */

  template<typename T>
  class segtree {
    private:
      int s, e, m;
      //covers s,e;
      T segment;
      segtree *l, *r;

    public:
      segtree(int a, int b) {
        s = a;
        e = b;
        if (s != e) {
          m = (s+e)/2;
          l = new segtree(s,m);
          r = new segtree(m+1,e);
        }
        else {
          l = nullptr;
          r = nullptr;
        }
      }

      void update(int i, T x) {
        if (s == e) {
          segment = x;
          return;
        }
        if (i <= m) {
          l->update(i,x);
        }
        else if (i > m) {
          r->update(i,x);
        }
        else assert(false);
        segment = merge_segment(l->segment, r->segment);
      }

      T getsum(int st, int en) {
        if (st <= s && e <= en) {
          return segment;
        }
        if (st <= m && en > m)
          return merge_segment(l->getsum(st,en), r->getsum(st,en));
        else if (st <= m)
          return l->getsum(st,en);
        else if (en > m)
          return r->getsum(st,en);
        else assert(false);
      }
  };
}
using Segtree::segtree;

struct pstack {
  int len;
  char start, end;

  pstack() { 
    len = 0;
  }
  pstack(char c) {
    len = 1;
    start = c;
    end = c;
  }
  pstack(int _len, char _start, char _end) {
    len = _len;
    start = _start;
    end = _end;
  }
};

char cflip(char c) {
  return c == '(' ? '[' : '(';
}
template<>
pstack Segtree::merge_segment(pstack a, pstack b) {
  if (a.len == 0) return b;
  else if (b.len == 0) return a;
  else if (a.end == b.start) {
    if (a.len == b.len) return pstack();
    else if (a.len > b.len) {
      int len = a.len - b.len;
      char end = (len % 2 == 1) ? a.start : cflip(a.start);
      return pstack(len, a.start, end);
    }
    else if (b.len > a.len) {
      int len = b.len - a.len;
      char start = (len % 2 == 1) ? b.end : cflip(b.end);
      return pstack(len, start, b.end);
    }
    else assert(false);
  }
  else {
    return pstack(a.len + b.len, a.start, b.end);
  }
}

void solve() {
  string s; cin >> s;
  int n = sz(s);
  int q; cin >> q;

  segtree<pstack> seg(0, n);
  F0R(i, n) {
    char c;
    if (s[i] == '(' || s[i] == ')') c = '(';
    else c = '[';
    seg.update(i, pstack(c));
  }
  /*
  F0R(i, n) {
    cout << i << ": " << seg.getsum(i,i).start << endl;
  }
  */
  while (q--) {
    int l, r; cin >> l >> r;
    l--; r--;
    auto s = seg.getsum(l, r);  
    cout << s.len/2 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
