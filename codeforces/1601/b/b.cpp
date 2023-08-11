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
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << " ";
  }
  return o;
}
// }}}

const int maxn = 300005;
int a[maxn], b[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }

  vector<int> PrevLevel(n+1, -1);
  set<int> unused;
  for (int i = 0; i < n; i++) unused.insert(i);
  queue<int> q; q.push(n);
  int cnt = 0;
  while (!q.empty()) {
    queue<int> nq;
    /*
    cout << "iteration " << cnt++ << '\n';
    cout << unused << endl;
    */
    while (!q.empty()) {
      int i = q.front(); q.pop();
      //cout << "visiting " << i << '\n';
      int j = i + b[i];

      int l = j - a[j];
      int r = j;

      auto it = unused.lower_bound(l);
      vector<int> toRemove;
      while (it != unused.end() && *it <= r) {
        nq.push(*it);
        toRemove.push_back(*it);
        PrevLevel[*it] = i;
        ++it;
      }
      for (int x: toRemove) unused.erase(x);
    }

    q = nq;
  }

  if (PrevLevel[0] == -1) {
    cout << -1 << '\n';
  }
  else {
    vector<int> ans;
    int i = 0;
    while (i != n) {
      ans.push_back(i);
      i = PrevLevel[i];
    }
    reverse(all(ans));
    cout << ans.size() << '\n';
    cout << ans << '\n';
  }
}
