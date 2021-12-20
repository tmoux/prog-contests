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

  template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

  template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v)
  requires Container<U<T>> && (!requires(std::ostream o, T a) { operator<<(o, a); })
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

struct Pair;
Pair* nextLeft(Pair* p);
Pair* nextRight(Pair* p);

void print(Pair* p);

struct Pair {
  ll x;
  Pair *par = NULL;
  Pair *l, *r;
  Pair(ll _x) {
    x = _x;
    l = r = NULL;
  }
  Pair(Pair* _l, Pair * _r) {
    l = _l;
    r = _r;
  }
  void setPar(Pair* _par) {
    par = _par;
  }
  Pair* clone() {
    Pair* ret = new Pair(x);
    ret->l = ret->r = NULL;
    ret->setPar(par);
    if (l) {
      ret->l = l->clone();
      ret->l->setPar(ret);
      ret->r = r->clone();
      ret->r->setPar(ret);
    }
    return ret;
  }
  ll magnitude() {
    if (l == NULL) {
      return x;
    }
    else {
      return l->magnitude() * 3 + r->magnitude() * 2;
    }
  }

  bool explode(int depth = 0) {
    if (l == NULL) return false;
    if (depth >= 4 && l != NULL && l->l == NULL && r->l == NULL) {
      Pair* left = nextLeft(this);
      Pair* right = nextRight(this);

      /*
      if (l->x == 6 && r->x == 7) {
        cout << "HI" << endl;
        cout << this->par->par->par->par << endl;
        print(this->par->par->par); cout << endl;
      }
      */
      if (left) left->x += l->x;
      if (right) right->x += r->x;

      // set to 0
      x = 0;
      l = r = NULL;
      return true;
    }
    else if (l->explode(depth+1)) {
      return true;
    }
    else {
      return r->explode(depth+1);
    }
  }

  bool split() {
    if (l == NULL) return false;
    if (l->l == NULL && l->x >= 10) {
      int nl = l->x / 2;
      int nr = l->x - nl;
      l = new Pair(new Pair(nl), new Pair(nr));
      l->setPar(this);
      l->l->setPar(l);
      l->r->setPar(l);
      return true;
    }
    else if (l->split()) {
      return true;
    }
    else if (r->l == NULL && r->x >= 10) {
      int nl = r->x / 2;
      int nr = r->x - nl;
      r = new Pair(new Pair(nl), new Pair(nr));
      r->setPar(this);
      r->l->setPar(r);
      r->r->setPar(r);
      return true;
    }
    else {
      return r->split();
    }
  }
};

void print(Pair* p) {
  if (p->l == NULL) {
    cout << p->x;
  }
  else {
    cout << "[";
    print(p->l);
    cout << ",";
    print(p->r);
    cout << "]";
  }
}

Pair* leftmost(Pair* p) { //return leftmost leaf
  if (p->l == NULL) return p;
  else return leftmost(p->l);
}
Pair* rightmost(Pair* p) { //return rightmost leaf
  if (p->l == NULL) return p;
  else return rightmost(p->r);
}
Pair* nextRight(Pair* p) {
  if (p->par == NULL) return NULL;
  else if (p == p->par->l) {
    return leftmost(p->par->r);
  }
  else return nextRight(p->par);
}
Pair* nextLeft(Pair* p) {
  if (p->par == NULL) return NULL;
  else if (p == p->par->r) {
    return rightmost(p->par->l);
  }
  else return nextLeft(p->par);
}

void reduce(Pair* p) {
  while (true) {
    if (p->explode()) {
      //cout << "exploding" << endl;
      //print(p); cout << endl;
      continue;
    }
    else if (p->split()) {
      //cout << "splitting" << endl;
      //print(p); cout << endl;
      continue;
    }
    else break;
    /*
    while (p->explode()) {
      cout << "exploding" << endl;
    }
    while (p->split()) {
      print(p); cout << endl;
    }
    */
  }
}

Pair* add(Pair* a, Pair* b) {
  Pair *x = a->clone();
  Pair *y = b->clone();
  Pair* ret = new Pair(x, y);
  x->setPar(ret);
  y->setPar(ret);
  reduce(ret);
  return ret;
}

pair<Pair*, int> parse(string_view s) {
  if (s[0] == '[') {
    auto [l, len1] = parse(s.substr(1));    
    auto [r, len2] = parse(s.substr(1+len1+1));
    int len = 1 + len1 + 1 + len2 + 1;
    Pair* ret = new Pair(l, r);
    l->setPar(ret);
    r->setPar(ret);
    return {ret, len};
  }
  else {
    return {new Pair(s[0]-'0'), 1};
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  vector<Pair*> pairs;
  while (cin >> s) {
    auto [p, _] = parse(s);
    pairs.push_back(p);
    //print(p); cout << endl;
  }
  //part 2
  ll maxans = 0;
  for (int i = 0; i < sz(pairs); i++) {
    for (int j = i+1; j < sz(pairs); j++) {
      ckmax(maxans, add(pairs[i], pairs[j])->magnitude());
      ckmax(maxans, add(pairs[j], pairs[i])->magnitude());
    }
  }
  cout << maxans << endl;

  return 0;
  Pair* sum = pairs[0];

  /*
  reduce(sum);
  print(sum); cout << endl;

  return 0;
  */
  for (int i = 1; i < sz(pairs); i++) {
    sum = add(sum, pairs[i]);
    print(sum); cout << endl;
  }

  cout << sum->magnitude() << endl;
}
