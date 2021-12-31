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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
// }}}

const int MAX_SCORE = 21;
const int POS = 10;
pair<ll,ll> dp[2][POS+1][POS+1][MAX_SCORE+11][MAX_SCORE+11];

pair<ll,ll> operator*(ll x, pair<ll,ll> a) {
  return {x*a.first, x*a.second};
}

pair<ll,ll>& operator+=(pair<ll,ll>& a, pair<ll,ll> b) {
  a.first += b.first;
  a.second += b.second;
  return a;
}

int freq[10];

pair<ll,ll> calc(int turn, int p1, int p2, int p1_score, int p2_score) {
  auto& ret = dp[turn][p1][p2][p1_score][p2_score];
  if (ret.first != -1) return ret;
  if (p1_score >= MAX_SCORE) {
    return ret = {1, 0};
  }
  else if (p2_score >= MAX_SCORE) {
    return ret = {0, 1};
  }
  ret = {0, 0};
  if (turn == 0) {
    //p1 turn
    for (int sum = 3; sum <= 9; sum++) {
      int np1 = (p1 + sum - 1) % 10 + 1;
      ret += freq[sum] * calc(turn^1, np1, p2, p1_score + np1, p2_score);
    }
  }
  else {
    //p2 turn
    for (int sum = 3; sum <= 9; sum++) {
      int np2 = (p2 + sum - 1) % 10 + 1;
      ret += freq[sum] * calc(turn^1, p1, np2, p1_score, p2_score + np2);
    }
  }
  return ret;
}

void solve(int p1, int p2) {
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      for (int k = 1; k <= 3; k++) {
        freq[i+j+k]++;
      }
    }
  }
  memset(dp, -1, sizeof dp);
  auto [num_p1, num_p2] = calc(0, p1, p2, 0, 0);  
  cout << max(num_p1, num_p2) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int p1 = 8, p2 = 5;
  solve(p1, p2);

  return 0;
  int p1_score = 0, p2_score = 0;
  int turns = 0;
  int dice = 1;

  auto roll_dice = [&]() -> int {
    int ret = dice;
    dice++; if (dice > 100) dice = 1;
    turns++;
    return ret;
  };
  while (true) {
    int add = roll_dice() + roll_dice() + roll_dice();

    p1 = (p1 + add - 1) % 10 + 1;
    p1_score += p1;

    if (p1_score >= 1000) {
      break;
    }

    add = roll_dice() + roll_dice() + roll_dice();

    p2 = (p2 + add - 1) % 10 + 1;
    p2_score += p2;

    if (p2_score >= 1000) {
      break;
    }
  }

  int ans = min(p1_score, p2_score) * turns;
  cout << ans << '\n';
}
