#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

const int maxk = 65;
int dp[maxk][6];

map<string, int> mp = {
  {"white",0},
  {"blue",1},
  {"red",2},
  {"orange",3},
  {"green",4},
  {"yellow",5},
};

map<ll,int> special;
map<ll,vector<ll>> specialChildren; //includes i if i is special

auto is_adj = [](int a, int b) {
  return (a != b) && (5-a != b);
};

map<pair<ll,int>,int> memo;

int calc(ll i, int level, int c) {
  if (memo.count({i,c})) return memo[make_pair(i,c)];
  int& res = memo[make_pair(i,c)];
  if (!specialChildren.count(i)) {
    return res = dp[level][c];
  }
  else if (special.count(i) && c != special[i]) {
    return res = 0;
  }
  else if (special.count(i) && level == 1) {
    return res = 1;
  }
  else {
    int left = 0;
    F0R(c1, 6) if (is_adj(c, c1)) {
      madd(left, calc(i*2, level-1, c1));
    }

    int right = 0;
    F0R(c2, 6) if (is_adj(c, c2)) {
      madd(right, calc(i*2+1, level-1, c2));
    }

    return res = mult(left, right);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int k; cin >> k;
  int n; cin >> n;
  F0R(_, n) {
    ll i; cin >> i;
    string s; cin >> s;
    special[i] = mp[s];

    ll j = i;
    while (j >= 1) {
      specialChildren[j].push_back(i);
      j /= 2;
    }
  }

  F0R(c, 6) {
    dp[1][c] = 1;
  }
  int cnt = 0;
  FOR(i, 2, k+1) {
    F0R(c, 6) {
      F0R(c1, 6) {
        F0R(c2, 6) {
          if (is_adj(c, c1) && is_adj(c, c2)) {
            //DEBUG(mult(dp[i-1][c1], dp[i-1][c2]));
            madd(dp[i][c], mult(dp[i-1][c1], dp[i-1][c2]));
          }
        }
      }
    }
  }

  int ans = 0;
  F0R(c, 6) {
    madd(ans, calc(1LL, k, c));
  }
  cout << ans << '\n';
}
