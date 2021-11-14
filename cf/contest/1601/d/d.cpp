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

struct LazySeg/*{{{*/
{
    int sz, *maxi, *lazy;
    LazySeg() {}
    LazySeg(int _n) {
        sz = _n;
        maxi = new int[4*(sz+1)+3];
        lazy = new int[4*(sz+1)+3];
        build(1,0,sz);
    }
    void build(int i, int a, int b) {
        if (a > b) return;
        maxi[i] = 0;
        lazy[i] = 0;
        if (a == b) {
            return;
        }
        build(i*2,a,(a+b)/2);
        build(i*2+1,(a+b)/2+1,b);
    }

    void push(int i, int a, int b) {
        if (a != b) {
            int m = (a+b)/2;
            lazy[i*2] += lazy[i];
            maxi[i*2] += lazy[i];

            lazy[i*2+1] += lazy[i];
            maxi[i*2+1] += lazy[i];
        }
        lazy[i] = 0;
    }

    void _add(int i, int a, int b, int st, int en, int x) {
        //lazy: already accounted for in your node, not the children
        if (st <= a && b <= en) {
            lazy[i] += x;
            maxi[i] += x;
            return;
        }
        push(i,a,b);
        int m = (a+b)/2;
        if (st <= m) {
            _add(i*2,a,m,st,en,x);
        }
        if (en > m) {
            _add(i*2+1,m+1,b,st,en,x);
        }

        maxi[i] = max(maxi[i*2], maxi[i*2+1]);
    }

    void add(int st, int en, int x) {
        _add(1,0,sz,st,en,x);
    }

    int _getmaxi(int i, int a, int b, int st, int en) {
        push(i,a,b);
        if (st <= a && b <= en) {
            return maxi[i];
        }
        int ret = 0;
        int m = (a+b)/2;
        if (st <= m) {
            ckmax(ret, _getmaxi(i*2,a,m,st,en));
        }
        if (en > m) {
            ckmax(ret, _getmaxi(i*2+1,m+1,b,st,en));
        }
        return ret;
    }

    int getmaxi(int st, int en) {
        return _getmaxi(1,0,sz,st,en);    
    }

    ~LazySeg() {
      delete[] maxi;
      delete[] lazy;
    }
};/*}}}*/

// overcounting...

int solve(vector<pair<int,int>> ps, int n) {
  map<int, vector<int>> mp;
  for (auto [x, y]: ps) {
    mp[y].push_back(x);
  }

  queue<pair<int,int>> toAdd;
  for (auto& [y, xs]: mp) {
    sort(all(xs));
    for (int x: xs) if (x >= y) toAdd.push({x, y});
  }

  priority_queue<pair<int,int>> toRemove;
  LazySeg seg(n);
  for (const auto& [y, xs]: mp) {
    while (!toAdd.empty() && toAdd.front().second < y) {
      auto [px, py] = toAdd.front(); toAdd.pop();
      if (py > 0) seg.add(0, py-1, 1);
      toRemove.push({px, py});
    }

    while (!toRemove.empty() && toRemove.top().first < y) {
      auto [px, py] = toRemove.top(); toRemove.pop();
      if (py > 0) seg.add(0, py-1, -1);
      cerr << "removing " << px << ' ' << py << endl;
    }


    int dp_val = 0;
    int y_add = 0;
    for (int x: xs) if (x >= y) y_add++;
    for (int x: xs) {
      //cerr << x << ' ' << y << ": " << seg->getmaxi(0, x) + y_add << endl;
      ckmax(dp_val, seg.getmaxi(0, x) + y_add + (x >= y ? 0 : 1));
      if (x >= y) y_add--;
    }

    int v = seg.getmaxi(y, y);
    if (dp_val > v) seg.add(y, y, dp_val - v);
  }

  return seg.getmaxi(0, n);
}

int main() {/*{{{*/
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, d; cin >> n >> d;
  const int maxn = 5e5+5;
  vector<pair<int,int>> points; points.reserve(maxn);
  vector<int> vals; vals.reserve(maxn);
  map<int, int> compress;
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    if (x >= d) {
      points.push_back({x, y});
      vals.push_back(x);
      vals.push_back(y);
    }
  }

  vals.push_back(d);
  sort(all(vals));
  int pt = 0;
  for (int i: vals) {
    if (!compress.count(i)) compress[i] = pt++;
  }
  for (int i = 0; i < sz(points); i++) {
    points[i].first = compress[points[i].first];
    points[i].second = compress[points[i].second];
  }

  int ans = solve(points, pt);
  cout << ans << '\n';
}/*}}}*/
