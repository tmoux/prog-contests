#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

string ANS;
int mode = 0;
char Prev;
int num_left = 0;

string ask(int p) {
  cout << p+1 << endl;
  string ret; cin >> ret;
  return ret;
  // string ans; ans += ANS[p];
  // if (mode == 0) {
  //   ans += '.';
  //   Prev = ANS[p];
  //   mode = 1;
  // }
  // else {
  //   if (Prev == ANS[p]) {
  //     num_left--;
  //     if (num_left == 0) ans += '!';
  //     else ans += '+';
  //   }
  //   else ans += '-';
  //   mode = 0;
  //   DEBUG(num_left);
  // }
  // return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string run; cin >> run;
  if (run == "prepare") {
    int T; cin >> T;
    REP(T) {
      string s; cin >> s;
      vector<vector<int>> pos(25);
      F0R(i, sz(s)) {
        pos[s[i]-'A'].push_back(i);
      }

      auto encode = [&](int x) -> string {
        string ans;
        F0R(i, 6) {
          if (x & (1 << i)) ans += '1';
          else ans += '0';
        }
        return ans;
      };
      string code;
      F0R(i, 4) {
        int p1 = pos[i][0];
        int p2 = pos[i][1];
        code += encode(p1);
        code += encode(p2);
      }
      code += "00";
      cout << code << endl;
    }
  }
  else if (run == "play") {
    int T; cin >> T;
    double total = 0;
    REP(T) {
      string s; cin >> s;
      int N = sz(s);
      num_left = N/2;
      vector<int> loc(N, -1);
      vector<bool> known(N, false);
      vector<pair<int, int>> tomatch;
      F0R(i, 4) {
        int p1 = 0;
        F0R(j, 6) {
          if (s[i*12+j] == '1') p1 += 1 << j;
        }
        int p2 = 0;
        F0R(j, 6) {
          if (s[i*12+6+j] == '1') p2 += 1 << j;
        }
        string r1 = ask(p1);
        string r2 = ask(p2);
        assert(r2[1] == '+');
        known[p1] = known[p2] = 1;
      }
      // ANS.clear();
      // F0R(i, 25) {
      //   ANS += (char)(i) + 'A';
      //   ANS += (char)(i) + 'A';
      // }

      // int N = 2*21;
      // num_left = N/2;
      // ANS.clear();
      // F0R(i, N/2) {
      //   ANS += (char)(i) + 'A';
      //   ANS += (char)(i) + 'A';
      // }
      // shuffle(all(ANS), rng);
      int miss = 0;

      while (1) {
        if (!tomatch.empty()) {
          auto [p1, p2] = tomatch.back(); tomatch.pop_back();
          ask(p1);
          ask(p2);
          continue;
        }
        int p1 = -1;
        F0R(i, N) {
          if (known[i]) continue;
          else {
            p1 = i;
            break;
          }
        }
        assert(p1 != -1);
        string r1 = ask(p1);
        string r2;
        known[p1] = true;
        if (loc[r1[0]-'A'] != -1) {
          // found match
          r2 = ask(loc[r1[0]-'A']);
        }
        else {
          loc[r1[0]-'A'] = p1;

          int p2 = -1;
          F0R(i, N) {
            if (known[i]) continue;
            else {
              p2 = i;
              break;
            }
          }
          assert(p2 != -1);
          r2 = ask(p2);
          if (r1[0] == r2[0]) {

          }
          else if (loc[r2[0]-'A'] != -1) {
            // found match
            tomatch.push_back({loc[r2[0]-'A'], p2});
            miss++;
          }
          else {
            loc[r2[0]-'A'] = p2;
            miss++;
          }
          known[p2] = true;
        }
        if (r2[1] == '!') break;
      }
      total += miss;
    }

    // cout << total << endl;
    // cout << fixed << setprecision(5) << total / T << endl;
  }
  else assert(false);
}
