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

const int maxn = 1e5+5;
int N, A[maxn];
int Left[maxn], Right[maxn];
int lptr[maxn], rptr[maxn];

int LeftV[maxn], RightV[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) {
    cin >> A[i];
  }

  multiset<int> ms;
  F0R(i, N) {
    if (i > 0 && A[i] > A[i-1]) {
      Left[i] = Left[i-1] + 1;
      lptr[i] = lptr[i-1];
    }
    else {
      Left[i] = 1;
      lptr[i] = i;
    }
    ms.insert(Left[i]);
  }
  F0Rd(i, N) {
    if (i + 1 < N && A[i] > A[i+1]) {
      Right[i] = Right[i+1] + 1;
      rptr[i] = rptr[i+1];
    }
    else {
      Right[i] = 1;
      rptr[i] = i;
    }
    ms.insert(Right[i]);
  }

  // leftv
  F0R(i, N) {
    LeftV[i] = i > 0 && A[i] < A[i-1] ? LeftV[i-1] + 1 : 1;
  }
  F0Rd(i, N) {
    RightV[i] = i + 1 < N && A[i] < A[i+1] ? RightV[i+1] + 1 : 1;
  }

  int ans = 0;
  F0R(i, N) {
    if (Left[i] > 1 && Right[i] > 1) {
      auto it = ms.find(Left[i]); ms.erase(it);
      it = ms.find(Right[i]); ms.erase(it);
      int x = max(Left[i], Right[i]);
      if (*ms.rbegin() < x) {
        bool p2 = false;
        {
          int a = Left[i]; if (a&1) a--;
          if (a-1 >= Right[i]-1) p2 = true;
        }
        {
          int a = Right[i]; if (a&1) a--;
          if (a-1 >= Left[i]-1) p2 = true;
        }
        {
          int j = lptr[i];
          if (LeftV[j] >= max(Left[i]-1, Right[i])) p2 = true;
        }
        {
          int j = rptr[i];
          if (RightV[j] >= max(Left[i], Right[i]-1)) p2 = true;
        }
        if (!p2) {
          // DEBUG(i);
          // cout << lptr[i] << ' ' << rptr[i] << endl;
          // cout << LeftV[lptr[i]] << endl;
          ans++;
        }
      }
      ms.insert(Left[i]);
      ms.insert(Right[i]);
    }
  }

  cout << ans << '\n';
}
