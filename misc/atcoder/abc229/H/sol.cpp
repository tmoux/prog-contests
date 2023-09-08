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

ll floor(ll a,ll b)
{
  if(b<0)a=-a,b=-b;
  return a>0 ? a/b : (a+b-1)/b;
}
ll ceil(ll a,ll b)
{
  if(b<0)a=-a,b=-b;
  return a>0 ? (a+b-1)/b : a/b;
}
// https://atcoder.jp/contests/abc229/submissions/44995638
struct SurrealNumber
{
  ll base,pow; // base*2^{-pow}
  SurrealNumber(ll _base=0,ll _pow=0):base(_base),pow(_pow)
  {
    assert(pow>=0);
    while(base%2==0 && pow>0)base/=2,--pow;
  }
  SurrealNumber operator + (const SurrealNumber& t)const
  {
    ll tpow=max(pow,t.pow);
    ll tbase=(base<<(tpow-pow))+(t.base<<(tpow-t.pow));
    return SurrealNumber(tbase,tpow);
  }
  SurrealNumber& operator += (const SurrealNumber& t)
  {
    return *this=*this+t;
  }
  bool operator < (const SurrealNumber& t)const
  {
    ll tpow=max(pow,t.pow);
    return (base<<(tpow-pow))<(t.base<<(tpow-t.pow));
  }
  int sgn()const
  {
    if(base>0)return 1;
    if(base<0)return -1;
    return 0;
  }
};
SurrealNumber getVal(const vector<SurrealNumber>& pL,const vector<SurrealNumber>& pR)
{
  if(pL.empty() && pR.empty())return 0;
  if(pL.empty())
  {
    SurrealNumber mR=*min_element(pR.begin(),pR.end());
    return min<ll>(0,floor(mR.base,1LL<<mR.pow)-1);
  }
  if(pR.empty())
  {
    SurrealNumber mL=*max_element(pL.begin(),pL.end());
    return max<ll>(0,ceil(mL.base,1LL<<mL.pow)+1);
  }
  SurrealNumber mL=*max_element(pL.begin(),pL.end());
  SurrealNumber mR=*min_element(pR.begin(),pR.end());
  assert(mL<mR);
  ll tpow=max(mL.pow,mR.pow);
  ll tbaseL=mL.base<<(tpow-mL.pow);
  ll tbaseR=mR.base<<(tpow-mR.pow);
  if(tbaseL<0 && tbaseR>0)return 0;
  int sgn=(tbaseL<0 || tbaseR<0 ? -1 : 1);
  if(sgn<0)tbaseL*=-1,tbaseR*=-1,swap(tbaseL,tbaseR);
  for(ll dpow=tpow;dpow>=0;dpow--)
    if(((tbaseR-1)>>dpow)>(tbaseL>>dpow))
      return SurrealNumber(sgn*((tbaseL>>dpow)+1),tpow-dpow);
  return SurrealNumber(sgn*(tbaseL<<1|1),tpow+1);
}

map<string, SurrealNumber> dp;

SurrealNumber eval(string s) {
  if (dp.count(s)) return dp[s];
  vector<SurrealNumber> pL, pR;
  F0R(i, sz(s)) {
    if (s[i] == 'B') {
      string t = s; t[i] = '.';
      pL.push_back(eval(t));
    }
    else if (i + 1 < sz(s) && s[i] == '.' && s[i+1] == 'W') {
      string t = s; swap(t[i], t[i+1]);
      pL.push_back(eval(t));
    }

    if (s[i] == 'W') {
      string t = s; t[i] = '.';
      pR.push_back(eval(t));
    }
    else if (i + 1 < sz(s) && s[i] == '.' && s[i+1] == 'B') {
      string t = s; swap(t[i], t[i+1]);
      pR.push_back(eval(t));
    }
  }
  return dp[s] = getVal(pL, pR);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<string> g(N);
  F0R(i, N) cin >> g[i];

  SurrealNumber ans;
  F0R(j, N) {
    string s; F0R(i, N) s += g[i][j];
    ans += eval(s);
  }
  cout << (ans.sgn() > 0 ? "Takahashi" : "Snuke") << '\n';
}
