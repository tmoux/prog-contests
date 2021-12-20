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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
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

const ll INF = 1e18;
struct Packet {
  int version;
  Packet(int _version) : version(_version) {}
  virtual string packet_string() = 0;
  virtual int sumVersions() = 0;
  virtual ll getVal() = 0;
};

struct LitPacket : Packet {
  ll number;
  LitPacket(int _version, ll _number) : Packet(_version), number(_number) {}
  string packet_string() {
    return "version: " + to_string(version) + " lit: " + to_string(number);
  }
  int sumVersions() {
    return version;
  }
  ll getVal() {
    return number;
  }
};

struct OpPacket : Packet {
  int op;
  vector<Packet*> subpackets;
  OpPacket(int _version, int _op, vector<Packet*> _subpackets) : 
    Packet(_version), 
    op(_op),
    subpackets(_subpackets) {}
  string packet_string() {
    string ret = "version: " + to_string(version) + " op: " + to_string(op) + "\n";
    for (auto p: subpackets) {
      ret += p->packet_string() + "\n";
    }
    return ret;
  }
  int sumVersions() {
    int sum = version;
    for (auto p: subpackets) {
      sum += p->sumVersions();
    }
    return sum;
  }
  ll getVal() {
    switch (op) {
      case 0: {
        ll ret = 0;
        for (auto p: subpackets) {
          ret += p->getVal();
        }
        return ret;
      }
      case 1: {
        ll ret = 1;
        for (auto p: subpackets) {
          ret *= p->getVal();
        }
        return ret;
      }
      case 2: {
        ll ret = INF;
        for (auto p: subpackets) {
          ckmin(ret, p->getVal());
        }
        return ret;
      }
      case 3: {
        ll ret = -INF;
        for (auto p: subpackets) {
          ckmax(ret, p->getVal());
        }
        return ret;
      }
      case 5: {
        assert(sz(subpackets) == 2);
        return subpackets[0]->getVal() > subpackets[1]->getVal();
      }
      case 6: {
        assert(sz(subpackets) == 2);
        return subpackets[0]->getVal() < subpackets[1]->getVal();
      }
      case 7: {
        assert(sz(subpackets) == 2);
        return subpackets[0]->getVal() == subpackets[1]->getVal();
      }
      default:
        assert(false);
    }
  }
};

ll binary_string_to_int(string_view s) {
  ll r = 0;
  for (char c: s) {
    r <<= 1;
    if (c == '1') r |= 1;
  }
  return r;
}

pair<ll, int> readLiteral(string_view data) {
  string r = "";
  int i = 0;
  while (true) {
    r += data.substr(i+1, 4);
    if (data[i] == '0') break;
    i += 5;
  }
  return {binary_string_to_int(r), i+5};
}

pair<Packet*, int> readPacket(string_view data) {
  int version = binary_string_to_int(data.substr(0, 3));
  int typeID = binary_string_to_int(data.substr(3, 3));
  int headerLen = 6;
  if (typeID == 4) {
    auto [lit, len] = readLiteral(data.substr(headerLen));
    return {new LitPacket(version, lit), headerLen + len};
  }
  else {
    vector<Packet*> subpackets;
    int lenTypeID = data[headerLen++] == '0' ? 0 : 1;
    if (lenTypeID == 0) {
      int subpacketLength = binary_string_to_int(data.substr(headerLen, 15));
      headerLen += 15;
      int curLen = 0;
      while (curLen < subpacketLength) {
        auto [packet, len] = readPacket(data.substr(headerLen + curLen));
        subpackets.push_back(packet);
        curLen += len;
      }
      return {new OpPacket(version, typeID, subpackets), headerLen + subpacketLength};
    }
    else {
      int numSubpackets = binary_string_to_int(data.substr(headerLen, 11));
      headerLen += 11;
      int curLen = 0;
      REP(numSubpackets) {
        auto [packet, len] = readPacket(data.substr(headerLen + curLen));
        subpackets.push_back(packet);
        curLen += len;
      }
      return {new OpPacket(version, typeID, subpackets), headerLen + curLen};
    }
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string line; cin >> line;
  auto convert = [](char c) -> string {
    switch (c) {
      case '0': return "0000";
      case '1': return "0001";
      case '2': return "0010";
      case '3': return "0011";
      case '4': return "0100";
      case '5': return "0101";
      case '6': return "0110";
      case '7': return "0111";
      case '8': return "1000";
      case '9': return "1001";
      case 'A': return "1010";
      case 'B': return "1011";
      case 'C': return "1100";
      case 'D': return "1101";
      case 'E': return "1110";
      case 'F': return "1111";
      default: assert(false);
    }
  };
  string data;
  for (char c: line) {
    data += convert(c);
  }

  auto [rootPacket, _] = readPacket(data);
  cout << rootPacket->packet_string() << endl;
  cout << rootPacket->sumVersions() << endl;
  cout << rootPacket->getVal() << endl;
}
