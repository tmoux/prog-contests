#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

int N;

string S;
int queries = 0;
int slow = 0;
int query(string s) {
  cout << s << endl;
  int x; cin >> x;
  // int x = 0; F0R(i, N) if (s[i] == S[i]) x++;
  if (x == N) {
    exit(0);
  }
  return x;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  string tt(N, 'T'), tf(N, 'T');
  for (int i = 1; i < N; i += 2) tf[i] = 'F';
  int Q1 = query(tt), Q2 = query(tf);
  string ans = tt;
  int idx = N-1;
  for (int i = 0; i < N;) {
    if (idx > i + 1) { // at least 3 left
      string s = tt;
      s[i] = s[i+1] = 'F';
      int q = query(s);
      int d = q - Q1;
      if (d == 2) {
        ans[i] = ans[i+1] = 'F';
      }
      else if (d == -2) {
        ans[i] = ans[i+1] = 'T';
      }
      else {
        assert(d == 0);
        auto flip = [](char c) {
          return c == 'F' ? 'T' : 'F';
        };
        string t = tf;
        t[i] = 'F', t[i+1] = 'T';
        t[idx] = flip(tf[idx]);
        q = query(t);
        d = q - Q2;
        if (d == 3) {
          ans[i] = 'F', ans[i+1] = 'T', ans[idx] = flip(tf[idx]);
        }
        else if (d == 1) {
          ans[i] = 'F', ans[i+1] = 'T', ans[idx] = tf[idx];
        }
        else if (d == -1) {
          ans[i] = 'T', ans[i+1] = 'F', ans[idx] = flip(tf[idx]);
        }
        else if (d == -3) {
          ans[i] = 'T', ans[i+1] = 'F', ans[idx] = tf[idx];
        }
        else assert(false);
        idx--;
      }
      i += 2;
    }
    else if (idx >= i) {
      string s = tt;
      s[i] = 'F';
      int q = query(s);
      int d = q - Q1;
      if (d == 1) ans[i] = 'F';
      else if (d == -1) ans[i] = 'T';
      else assert(false);
      i++;
    }
    else break;
  }
  query(ans);
}
