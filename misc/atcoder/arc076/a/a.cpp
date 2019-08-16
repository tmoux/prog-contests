#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9+7;
int fac(int x) {
    return x == 0 ? 1 : (1LL*x*fac(x-1)) % MOD;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    if (N < M) swap(N,M);
    if (N == M) {
        cout << ((1LL*2*fac(M)*fac(N)) % MOD) << '\n';
    }
    else if (M == N-1) {
        cout << ((1LL*fac(M)*fac(N))%MOD) << '\n';
    }
    else {
        cout << 0 << '\n';
    }

}

