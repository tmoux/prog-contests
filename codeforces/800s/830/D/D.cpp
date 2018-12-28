#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

template<int M>
struct mint
{
    ll val;
    mint(): val(0) {}
    mint(ll _v): val(_v) {}
    mint(const mint& _v): val(_v.val) {}

    mint& operator+=(const mint& rhs) {
        val = (rhs.val + M) % M;
        return *this;    
    }
    friend mint operator+(mint lhs, const mint& rhs) {
        lhs += rhs;
        return lhs;
    }
    mint& operator-=(const mint& rhs) {
        val = (val-rhs.val+M) % M;
        return *this;
    }
    friend mint operator-(mint lhs, const mint& rhs) {
        lhs -= rhs;
        return lhs;
    }
    mint& operator*=(const mint& rhs) {
        val = (val*rhs.val) % M;
        return *this;
    }
    friend mint operator*(mint lhs, const mint& rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend ostream& operator<<(ostream& stream, const mint& m) {
        stream << m.val;
        return stream;
    }
};
typedef mint<1000000007> m_int;

const int maxn = 405, M = 1e9+7;
int k;
m_int dp[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> k;
    dp[1][0] = m_int(1);
    dp[1][1] = m_int(1);
    for (int i = 2; i <= k; i++) {
        for (int p = 0; p <= k; p++) {
            for (int q = 0; q <= k-p; q++) {
                m_int x(dp[i-1][p] * dp[i-1][q]);
                //dp[i][p+q] += x*(2*
                /*
                dp[i][p+q] = (dp[i][p+q] + x * (2*(p+q) + 1)) % M;
                dp[i][p+q+1] = (dp[i][p+q+1] + x) % M;
                dp[i][p+q-1] = (dp[i][p+q-1] + (x*(p+q)*(p+q-1))%M) % M;
                */
            }
        }
    }
    cout << dp[k][1] << '\n';
    
    return 0;
}

