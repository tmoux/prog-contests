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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string S; cin >> S;
  char first = S[0];
  char last = S.back();
  map<pair<char, char>, ll> pairCount;
  F0R(i, sz(S)-1) {
    pairCount[{S[i], S[i+1]}]++;
  }


  map<pair<char, char>, char> rules;
  string pa, arr;
  char c;
  while (cin >> pa >> arr >> c) {
    rules[{pa[0], pa[1]}] = c;
  }

  int iter = 40;
  for (int t = 0; t < iter; t++) {
    cout << t << ":\n";
    for (auto [p, c]: pairCount) {
      cout << p.first << ' ' << p.second << ": " << c << endl;
    }

    map<pair<char, char>, ll> nmap;
    for (auto [p, c]: pairCount) {
      if (rules.count(p)) {
        nmap[{p.first, rules[p]}] += c;
        nmap[{rules[p], p.second}] += c;
      }
      else {
        nmap[p]++;
      }
    }
    pairCount = nmap;
  }

  map<char, ll> totals;
  for (auto [p, c]: pairCount) {
    totals[p.first] += c;
    totals[p.second] += c;
  }
  for (auto& [c, cnt]: totals) {
    cnt /= 2;
  }
  totals[first]++;
  totals[last]++;
  
  vector<ll> frequencies;
  for (auto& [c, cnt]: totals) {
    frequencies.push_back(cnt);
  }
  sort(all(frequencies));
  cout << frequencies.back() - frequencies.front() << endl;
}
