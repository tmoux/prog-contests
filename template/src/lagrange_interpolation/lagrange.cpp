namespace Poly {
  using poly = vector<mint>;

  mint eval(const poly& p, int x) { // evaluates p(x) at x
    mint res = 0;
    mint mul = 1;
    for (int i = 0; i < sz(p); i++) {
      res += mul * p[i];
      mul *= x;
    }
    return res;
  }

  poly operator*(const poly& a, const poly& b) {
    poly ans = vector<mint>(a.size()+b.size()-1);
    for (int i = 0; i < sz(a); i++) {
      for (int j = 0; j < sz(b); j++) {
        ans[i + j] += a[i] * b[j];
      }
    }
    return ans;
  }

  poly operator+(poly a, poly b) {
    if (a.size() < b.size()) swap(a, b);
    poly ans = a;
    for (int i = 0; i < sz(b); i++) {
      ans[i] += b[i];
    }
    return ans;
  }

  poly scale(const poly& a, mint s) {
    poly ans = a;
    for (auto& i: ans) {
      i *= s;
    }
    return ans;
  }

  ostream& operator<<(ostream& os, const poly& p) {
    for (int i = 0; i < sz(p); i++) {
      if (i == 0) os << p[i];
      else os << p[i] << "x^" << i;
      if (i < sz(p)-1) os << " + ";
    }
    return os;
  }

  poly interpolate(vector<pair<int, mint>> qs) {
    poly f;
    for (auto p: qs) {
      auto [x, y] = p;
      poly r = {1};
      for (auto q: qs) {
        if (p == q) continue;
        poly m = {mint(-q.first), 1};
        r = r * m;
      }
      for (auto q: qs) {
        if (p == q) continue;
        r = scale(r, mint(x - q.first).inverse());
      }
      r = scale(r, y);
      f = f + r;
    }
    return f;
  }
}
using namespace Poly;
