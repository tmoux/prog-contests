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

int ask_or(int i, int j) {
  cout << "or " << i << ' ' << j << endl;
  int x; cin >> x;
  return x;
}

int ask_and(int i, int j) {
  cout << "and " << i << ' ' << j << endl;
  int x; cin >> x;
  return x;
}

void answer(int x) {
  cout << "finish " << x << endl;
}

const int maxn = 10005;
int n, k;
int a[maxn];
const int bits = 29;

int and_ans[4], or_ans[4];
int ans[maxn];

void init() {
  cin >> n >> k;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init();

  and_ans[1] = ask_and(1, 2);
  and_ans[2] = ask_and(2, 3);
  and_ans[3] = ask_and(3, 1);
  or_ans[1] = ask_or(1, 2);
  or_ans[2] = ask_or(2, 3);
  or_ans[3] = ask_or(3, 1);

  auto get_bit = [](int x, int b) {
    return (x>>b)&1;
  };

  for (int b = 0; b <= bits; b++) {
    int bit = -1;
    int and_12 = get_bit(and_ans[1], b);
    int and_23 = get_bit(and_ans[2], b);
    int and_13 = get_bit(and_ans[3], b);
    int or_12 = get_bit(or_ans[1], b);
    int or_23 = get_bit(or_ans[2], b);
    int or_13 = get_bit(or_ans[3], b);
    if (or_23 == 0) {//2 = 0, 3 = 0
      bit = or_12;
    }
    else if (and_12 == 0 && and_13 == 0) bit = 0;
    else bit = 1;
    assert(bit == 0 || bit == 1);
    ans[1] |= bit<<b;
  }

  for (int i = 2; i <= n; i++) {
    int and_1i = i == 2 ? and_ans[1] : i == 3 ? and_ans[3] : ask_and(1, i);
    int or_1i = i == 2 ? or_ans[1] : i == 3 ? or_ans[3] : ask_or(1, i);

    for (int b = 0; b <= bits; b++) {
      int bit = get_bit(ans[1], b) == 0 ? get_bit(or_1i, b) : get_bit(and_1i, b);
      ans[i] |= bit<<b;
    }
  }
  sort(ans+1,ans+1+n);
  answer(ans[k]);
}
