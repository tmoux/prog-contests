#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
 
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
 
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
 
#define sz(x) (int)(x).size()
#define f first
#define s second
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

inline uint hex_to_int(char s){
    if (s <= '9') return s - '0';
    else return (s - 'a' + 10);
}
 
inline uint substr_to_int(string s,int l,int r){
    uint ret = 0;
    for (int i = l*2;i < r*2;i++){
        ret = ret * 16 + hex_to_int(s[i]);
    }
    return ret;
}
 
uint f(uint x,uint ka,uint kb,uint delta){
    return (~x + delta) ^ ((x >> 3) + ka) ^ ((x << 13) + kb);
}
 
string go_hex(uint n){
    string ans = "";
    for (int i = 0;i < 8;i++){
        int id = n % 16;
        if (id < 10)  ans = ans + (char)('0' + id);
        else ans = ans + (char)('a' + id - 10);
        n /= 16;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
 
void encrypt(string data,string key){
    uint k0 = substr_to_int(key,0,4);
    uint k1 = substr_to_int(key,4,8);
    uint k2 = substr_to_int(key,8,12);
    uint k3 = substr_to_int(key,12,16);
    uint l = substr_to_int(data,0,4);
    uint r = substr_to_int(data,4,8);
    uint tri = 0;
    uint delta = 0xBB40E64D;
    int n = 64;
    while (n > 0){
        tri = tri + delta;
        l = l ^ f(r,k0,k1,tri);
        r = r ^ f(l,k2,k3,tri);
        n--;
    }
    cout << go_hex(r) << go_hex(l) << endl;
}
 
void decrypt(string data,string key){
  uint k0 = substr_to_int(key,0,4);
  uint k1 = substr_to_int(key,4,8);
  uint k2 = substr_to_int(key,8,12);
  uint k3 = substr_to_int(key,12,16);
  uint l = substr_to_int(data,0,4);
  uint r = substr_to_int(data,4,8);
  uint tri = 0xd0399340;
  uint delta = 0xBB40E64D;
  int n = 64;
  while (n > 0){
      l = l ^ f(r,k2,k3,tri);
      r = r ^ f(l,k0,k1,tri);
      tri = tri - delta;
      n--;
  }
  cout << go_hex(r) << go_hex(l) << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string encrypt, mode;
  cin >> encrypt >> mode;
  if (encrypt == "ENCRYPT")
}
