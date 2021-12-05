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

  template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

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

struct Bingo {
  int board[5][5];
  bool marked[5][5];

  Bingo() {
    memset(board, 0, sizeof board);
    memset(marked, 0, sizeof marked);
  }

  void mark_square(int x) {
    F0R(i, 5) {
      F0R(j, 5) {
        if (board[i][j] == x) {
          marked[i][j] = true;
        }
      }
    }
  }
  bool has_bingo() {
    F0R(i, 5) {
      bool poss = true;
      F0R(j, 5) {
        if (!marked[i][j]) {
          poss = false;
          break;
        }
      }
      if (poss) return true;
    }
    F0R(j, 5) {
      bool poss = true;
      F0R(i, 5) {
        if (!marked[i][j]) {
          poss = false;
          break;
        }
      }
      if (poss) return true;
    }
    return false;
  }

  int get_score(int x) {
    int sum = 0;
    F0R(i, 5) {
      F0R(j, 5) {
        if (!marked[i][j]) {
          sum += board[i][j];
        }
      }
    }
    return sum * x;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  getline(cin, s);
  stringstream ss(s);

  vector<int> nums;
  int x;
  while (ss >> x) {
    nums.push_back(x);
  }

  int n = 100;
  vector<Bingo> cards;
  F0R(_, n) {
    Bingo b;
    F0R(i, 5) {
      F0R(j, 5) {
        cin >> b.board[i][j];
      }
    }

    F0R(i, 5) {
      F0R(j, 5) {
        cout << b.board[i][j] << ' ';
      }
      cout << '\n';
    }
    cout << '\n';
    cards.push_back(b);
  }


  int cnt = 0;
  for (int x: nums) {
    cout << "x = " << x << endl;
    for (auto& b: cards) {
      if (b.has_bingo()) continue;
      b.mark_square(x);
      if (b.has_bingo()) {
        int ans = b.get_score(x);
        cout << "ANS " << cnt++ << ": " << ans << endl;

        F0R(i, 5) {
          F0R(j, 5) {
            cout << b.marked[i][j] << ' ';
          }
          cout << '\n';
        }
        cout << '\n';
      }

    }
  }
}
