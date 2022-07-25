#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

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

int N, M;
const int maxn = 1005;

const ld eps = 1e-7;

ld AX[maxn], BX[maxn], CX[maxn], DX[maxn];
ld AY[maxn], BY[maxn], CY[maxn], DY[maxn];

ld eval_x(int i, ld t) {
  return AX[i] * t * t * t + BX[i] * t * t + CX[i] * t + DY[i];
}

ld eval_y(int i, ld t) {
  return AY[i] * t * t * t + BY[i] * t * t + CY[i] * t + DY[i];
}

ld y_deriv(int i, ld t) {
  return 3 * AY[i] * t * t + 2 * BY[i] * t + CY[i];
}

// http://www.realitypixels.com/turk/opensource/FindCubicRoots.c.txt
int FindCubicRoots(const ld coeff[4], ld x[3])
{
  ld a1 = coeff[2] / coeff[3];
  ld a2 = coeff[1] / coeff[3];
  ld a3 = coeff[0] / coeff[3];

  ld Q = (a1 * a1 - 3 * a2) / 9;
  ld R = (2 * a1 * a1 * a1 - 9 * a1 * a2 + 27 * a3) / 54;
  ld Qcubed = Q * Q * Q;
  ld d = Qcubed - R * R;

  /* Three real roots */
  if (d >= 0) {
    ld theta = acos(R / sqrt(Qcubed));
    ld sqrtQ = sqrt(Q);
    x[0] = -2 * sqrtQ * cos( theta             / 3) - a1 / 3;
    x[1] = -2 * sqrtQ * cos((theta + 2 * M_PI) / 3) - a1 / 3;
    x[2] = -2 * sqrtQ * cos((theta + 4 * M_PI) / 3) - a1 / 3;
    return (3);
  }

  /* One real root */
  else {
    ld e = pow(sqrt(-d) + fabs(R), 1. / 3.);
    if (R > 0)
      e = -e;
    x[0] = (e + Q / e) - a1 / 3.;
    return (1);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) {
    cin >> AX[i] >> BX[i] >> CX[i] >> DX[i];
    cin >> AY[i] >> BY[i] >> CY[i] >> DY[i];
  }

  int M; cin >> M;
  REP(M) {
    ld X, Y; cin >> X >> Y;

    int wind = 0;
    F0R(i, N) {
      ld coeff[] = {DY[i], CY[i], BY[i], AY[i]};
      coeff[0] -= Y;

      ld t[3];
      int roots = FindCubicRoots(coeff, t);
      F0R(j, roots) {
        ld x = eval_x(i, t[j]);
        ld y = eval_y(i, t[j]);

        if (eps < t[j] && t[j] < 1-eps) {
          /*
          DEBUG(i);
          cout << t[j] << endl;
          cout << y << ' ' << Y << ": " << abs(y - Y) << endl;
          assert(abs(y - Y) < eps);
          */

          // y should be Y

          if (x > X + eps) {
            // calculate derivative of y
            ld deriv = y_deriv(i, t[j]);
            DEBUG(deriv);
            if (deriv > eps) wind++;
            else wind--;
          }
        }
      }
    }

    cout << (wind == 0 ? 0 : 1) << '\n';
  }
}
