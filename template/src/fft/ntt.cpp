const int mod = 998244353, root = 62;
using mint = ModInt::mod_int<mod>;

template<typename T, unsigned ROOT>
struct NTT {
  void ntt(vector<T> &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<T> rt(2, 1);
    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
      rt.resize(n);
      T z[] = {1, T(root) ^ (mod >> s)};
      FOR(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1];
    }
    vector<int> rev(n);
    FOR(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    FOR(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
      for (int i = 0; i < n; i += 2 * k) FOR(j,0,k) {
          mint z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
          a[i + j + k] = ai - z;
          ai += z;
        }
  }
  vector<T> conv(const vector<T> &a, const vector<T> &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    mint inv = 1 / mint(n);
    vector<T> L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    FOR(i,0,n) out[-i & (n - 1)] = L[i] * R[i] * inv;
    ntt(out);
    return {out.begin(), out.begin() + s};
  }
};

