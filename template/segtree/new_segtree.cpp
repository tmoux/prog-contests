#include <bits/stdc++.h>

namespace Segtree {
  template<typename T> 
  T merge_segment(T a, T b);

  /*
  template<typename T>
  concept Segment = requires(T a, T b) {
    { merge_segment<T>(a, b) } -> std::same_as<T>;
  };
  */

  //template<Segment T>
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
