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

// TODO: Make this FAST

vector<int> indices[10] = {
  {0, 1, 2, 4, 5, 6},
  {2, 5},
  {0, 2, 3, 4, 6},
  {0, 2, 3, 5, 6},
  {1, 2, 3, 5},
  {0, 1, 3, 5, 6},
  {0, 1, 3, 4, 5, 6},
  {0, 2, 5},
  {0, 1, 2, 3, 4, 5, 6},
  {0, 1, 2, 3, 5, 6}
};
bool matches(string s, int d, const vector<char>& p) {
  if (sz(s) != sz(indices[d])) return false;
  else {
    sort(all(s));
    string t;
    for (int i = 0; i < sz(indices[d]); i++) {
      t += p[indices[d][i]];
    }
    sort(all(t));
    return s == t;
  }
}

map<string, int> all_matches(const vector<string>& vs, const vector<char>& p) {
  map<string, int> code;
  F0R(i, sz(vs)) {
    bool poss = false;
    for (int d = 0; d < 10; d++) {
      if (matches(vs[i], d, p)) {
        poss = true;
        code[vs[i]] = d;
        break;
      }
    }
    if (!poss) return {};
  }
  return code;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  string line;

  int answer = 0;
  int tc = 1;
  while (getline(cin, line)) {
    cout << "Test case " << tc++ << endl;
    stringstream ss(line);
    string s;
    vector<string> vs;
    while (ss >> s) {
      if (s == "|") break;
      else vs.push_back(s);
    }

    vector<char> p;
    for (char c = 'a'; c <= 'g'; c++) {
      p.push_back(c);
    }

    map<string, int> code;
    do {
      code = all_matches(vs, p);
      if (!code.empty()) break;
    } while (next_permutation(all(p)));

    assert(!code.empty());
    for (auto [s, d]: code) {
      cout << "OK\n";
      cout << s << ": " << d << endl;
    }

    int num = 0;
    while (ss >> s) {
      sort(all(s));
      num = num * 10 + code[s];
    }
    cout << "num " << num << endl;
    answer += num;
    cout << "sum so far = " << answer << endl;
  }
  cout << answer << '\n';
}
