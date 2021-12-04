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

// }}}

namespace superIO {/*{{{*/
	//only for reading ints/lls
	//really only useful when input is greater than 10^6
	//but it is super fast
	int BUF=100000;
	int buf_readed = 0;
	int buf_index = 0;
	char buffer[100000];
	char my_getchar(){
	    char x;
	    if(buf_index==buf_readed){
	        buf_index=0;
	        buf_readed=fread(buffer,1,BUF,stdin);
	    }   
	    x=buffer[buf_index];
	    buf_index++;
	    return x;
	}

	//can return int or long long
	int getInt() {
	    int r=0;
	    char c;
	    int sign=1;
	    while(1){
	        c=my_getchar();
	        if(c=='-')
	            sign=-1;
	 
	        if((c>='0' && c<='9')){
	            r=(c-'0');
	            break;
	        }
	    }
	    while(1){
	        c=my_getchar();
	            if(!(c>='0' && c<='9'))
	                break;
	        r=r*10+(c-'0');
	    }
	    return sign*r;
	}
}/*}}}*/
using namespace superIO;

template<int maxn>
int solve(int n, vector<int> a, vector<bool> c) {
  auto calc = [](const vector<pair<int,int>>& mins, pair<int,int> mx) {
    if (mins[0].second != mx.second) {
      return mx.first - mins[0].first;
    }
    else return mx.first - mins[1].first;
  };

  bitset<maxn> ones;
  bitset<maxn> bs;
  for (int i = 0; i < n; i++) {
    bs[i] = c[i];
    ones[i] = 1;
  }
  auto is_diff_k = [&](int k) -> bool {
    return bs == (((bs >> k) | (bs << (n-k))) & ones);
  };
  for (int d = 2; d < n; d++) {
    if (n % d == 0) {
      bool poss = is_diff_k(d);
      if (poss) {
        vector<pair<int,int>> mins, maxs;
        for (int i = 0; i < d; i++) {
          int mn = a[i];
          int mx = a[i];
          for (int j = i; j < n; j += d) {
            ckmin(mn, a[j]);
            ckmax(mx, a[j]);
          }
          mins.push_back({mn, i});
          maxs.push_back({mx, i});
        }
        sort(all(mins));
        sort(all(maxs)); reverse(all(maxs));

        return max(calc(mins, maxs[0]), calc(mins, maxs[1]));
      }
    }
  }

  int ans = *max_element(all(a)) - *min_element(all(a));
  return ans;
}

template<int i>
int solve_n(int n, vector<int> a, vector<bool> c) {
  if (n <= (1<<i)) return solve<1<<i>(n, a, c);
  else return solve_n<i+1>(n, a, c);
}

template<>
int solve_n<21>(int n, vector<int> a, vector<bool> c) {
  return solve<1<<21>(n, a, c);
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T = getInt();
  while (T--) {
    int n = getInt();
    vector<int> a(n);
    for (auto& i: a) i = getInt();
    vector<bool> c(n);
    for (int i = 0; i < n; i++) {
      c[i] = my_getchar() == 'W'; // don't think it matters which is 0/1
    }

    int my = solve_n<0>(n, a, c);
    cout << my << '\n';
  }
}

