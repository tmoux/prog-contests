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

/*
  template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v)
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
*/
// }}}

void solve() {
  string S; cin >> S;
  //cout << "testing " << S << endl;
  int N = sz(S);
  int one_count = count(all(S), '1');

  if (one_count == 0) {
    cout << "YES\n";
    cout << 0 << '\n';
    return;
  }
  else {
    auto flip = [](char& c) {
      c = c == '0' ? '1' : '0';
    };
    auto add_op = [&flip](int index, int type, string& S, vector<int>& v) {
      v.push_back(index); 
      if (type == 2) {
        flip(S[index]);
      }
      else {
        flip(S[index]);
        flip(S[index+1]);
        flip(S[index+2]);
      }
    };
    vector<int> ans;

    int parity = one_count % 2;
    int start = parity == 0 ? 1 : 2;
    if (parity == 1) {
      //find the first one to set to set to 0
      auto idx = S.find('1');
      assert(idx != string::npos);
      add_op(idx, 2, S, ans);
      //cout << "fixing parity" << endl;
    }

    auto pivot = S.find('0'); 
    if (pivot == string::npos) { //all ones; impossible
      cout << "NO\n";
      return;
    }
    else {
      auto calc = [&add_op](string& S) -> vector<int> {/*{{{*/
        vector<int> res;
        for (int i = 0; i + 3 <= sz(S); i++) {
          if (i + 3 == sz(S)) { //last triple
            assert((S[i] == '1' && S[i+1] == '1' && S[i+2] == '1') % 2 == 0);
            if (S[i] == '0' && S[i+1] == '0' && S[i+2] == '0') {
              continue;
            }
            else if (S[i] == '0' && S[i+1] == '1' && S[i+2] == '1') {
              add_op(i, 1, S, res);
              add_op(i, 2, S, res);
            }
            else if (S[i] == '1' && S[i+1] == '0' && S[i+2] == '1') {
              add_op(i, 1, S, res);
              add_op(i+1, 2, S, res);
            }
            else if (S[i] == '1' && S[i+1] == '1' && S[i+2] == '0') {
              add_op(i, 1, S, res);
              add_op(i+2, 2, S, res);
            }
          }
          else if (S[i] == '0') continue;
          else { //handle 4 cases
            if (S[i+1] == '0' && S[i+2] == '0') {
              add_op(i, 1, S, res);
              add_op(i+1, 2, S, res);
            }
            else if (S[i+1] == '0' && S[i+2] == '1') {
              add_op(i, 1, S, res);
              add_op(i+1, 2, S, res);
            }
            else if (S[i+1] == '1' && S[i+2] == '0') {
              add_op(i, 1, S, res);
              add_op(i+2, 2, S, res);
            }
            else if (S[i+1] == '1' && S[i+2] == '1') {
              assert(S[i-1] == '0');
              add_op(i-1, 1, S, res);
              add_op(i-1, 2, S, res);
            }
          }
        }
        return res;
      };/*}}}*/
      // If left and right partitions both have odd parity,
      // flip them both to correct both partitions.
      int left_count = count(S.begin(), S.begin()+pivot, '1');
      if (left_count % 2 == 1) {
        add_op(pivot-1, 1, S, ans);
        add_op(pivot, 2, S, ans);
      }

      //cout << "S = " << S << endl;
      //cout << "pivot = " << pivot << endl;
      string s = S.substr(pivot);
      string t = S.substr(0, pivot+1); reverse(all(t));

      //cout << "s = " << s << endl;
      //cout << "t = " << t << endl;

      auto ans_s = calc(s);
      auto ans_t = calc(t);

      //cout << "s = " << s << endl;
      //cout << "t = " << t << endl;

      for (int i: ans_s) ans.push_back(i+pivot);
      for (int i = 0; i < sz(ans_t); i++) {
        if (i % 2 == 0) ans.push_back(pivot-ans_t[i]-2);
        else ans.push_back(pivot-ans_t[i]);
      }


      //output
      cout << "YES\n";
      cout << ans.size() << '\n';
      cout << start << '\n';
      for (int i: ans) {
        cout << i << '\n';
      }
      assert(all_of(all(s), [](char c){return c == '0';}));
      assert(all_of(all(t), [](char c){return c == '0';}));
      assert(sz(ans) <= N);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
