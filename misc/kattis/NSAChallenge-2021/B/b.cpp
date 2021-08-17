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

namespace Parsing {
  int hex_to_int(char c) {
    if ('0' <= c && c <= '9') return c-'0';
    else return c-'a'+10;
  }

  int get_byte(char a, char b) {
    return hex_to_int(a)*16 + hex_to_int(b);
  }

  const int HEADER_LEN = 12;

  map<int,string> tagName = {
    {0x01, "VICTIM_ID"},
    {0x02, "VERSION"},
    {0x06, "FILENAME"},
    {0x08, "IV"},
    {0x09, "NONCE"},
    {0x13, "KEY_HASH"},
    {0x27, "ENC_DATA"}
  };

  map<int,bool> isRawData = {
    {0x01, false},
    {0x02, false},
    {0x06, false},
    {0x08, true},
    {0x09, true},
    {0x13, false},
    {0x27, true}
  };

  int get_tag(const string& s, int& i) {
    int byte = get_byte(s[i],s[i+1]);
    i += 2;
    return byte;
  }

  int get_length(const string& s, int& i) {
    int length = 0;
    int byte;
    do {
      byte = get_byte(s[i],s[i+1]);
      int data = byte & ((1<<7)-1);
      length *= 128;
      length += data;
      i += 2;
    } while (byte & (1<<7));
    return length;
  }

  string get_value(const string& s, int& i, int length, bool isRaw) {
    if (isRaw) {
      string ret = s.substr(i,2*length);
      i += 2*length;
      return ret;
    }
    else {
      string ret = "";
      F0R(_, length) {
        int byte = get_byte(s[i],s[i+1]);
        ret += (char)byte;
        i += 2;
      }
      return ret;
    }
  }

  //returns list of (tag, value)
  vector<pair<string,string>> parse(string s) {
    vector<pair<string,string>> ret;
    int cur = 0;

    while (cur < s.size()) {
      int tag = get_tag(s, cur);
      int length = get_length(s, cur);
      bool isRaw = isRawData.count(tag) ? isRawData[tag] : true;
      string value = get_value(s, cur, length, isRaw);
      string tagname = tagName.count(tag) ? tagName[tag] : "UNKNOWN";
      ret.push_back({tagname,value});
    }
    //assert(cur == s.size());
    return ret;
  }
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; cin >> s;
  //for (auto p: Parsing::parse(s.substr(Parsing::HEADER_LEN*2))) {
  for (auto p: Parsing::parse(s)) {
    cout << p.first << ":" << p.second << '\n';
  }
}
