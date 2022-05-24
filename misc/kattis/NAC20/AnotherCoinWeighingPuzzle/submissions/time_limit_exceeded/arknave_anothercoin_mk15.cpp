#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 998244353;

struct modint {
    int v;
    modint(const int _v = 0): v(_v % MOD) {
        if (v < 0) v += MOD;
    }

    void operator+=(const modint& o) {
        v += o.v;
        if (v >= MOD)
            v -= MOD;
    }

    void operator-=(const modint& o) {
        v -= o.v;
        if (v < 0)
            v += MOD;
    }

    modint operator*=(const modint& o) {
        v = 1LL * v * o.v % MOD;
        return *this;
    }

    modint operator*(const modint& o) const {
        return modint(v) *= o;
    }

    static modint modpow(const modint& b, int e) {
        if (e == 0) return 1;
        modint x = modpow(b * b, e / 2);
        return (e % 2) ? b * x : x;
    }

    modint inv() const {
        return modpow(*this, MOD - 2);
    }

    friend ostream& operator<<(ostream& os, modint const& m) {
        return os << m.v;
    }
};

constexpr int MAXN = 2e5 + 5;

modint fact[MAXN], tcaf[MAXN];

void gen_fact() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    tcaf[MAXN - 1] = fact[MAXN - 1].inv();
    for (int i = MAXN - 2; i >= 0; --i) {
        tcaf[i] = tcaf[i + 1] * (i + 1);
    }
}

modint choose(int n, int k) {
    if (k < 0 or k > n) return 0;
    return fact[n] * tcaf[k] * tcaf[n - k];
}

map<int, int> memo;
modint solve(int m, int k) {
    if (m == 0) return 1;
    if (m == 1) return 1;
    auto it = memo.find(k);
    if (it != end(memo))
        return it->second;

    // k options per cell
    modint res = modint::modpow(k, m);
    // there's only sqrt(k) values that we care about
    for (int j = 2, nxt; j <= k; j = nxt + 1) {
        nxt = k / (k / j);
        int len = nxt - j + 1;
        res -= solve(m, k / j) * len;
    }

    return memo[k] = res.v;
}

int main() {
    gen_fact();

    int m, k;
    cin >> m >> k;

    modint ans = 0;
    modint pow2 = 1;
    for (int zeros = m; zeros >= 0; --zeros, pow2 *= 2) {
        // number of ways to place the zeros
        memo.clear();
        modint cur = pow2 * choose(m, zeros) * solve(m - zeros, k);
        ans += cur;
    }

    cout << ans << '\n';

    return 0;
}
