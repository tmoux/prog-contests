#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ull MOD = 1e9+7;

struct Matrix
{
    ull d[2][2];
    Matrix operator*(Matrix r) {
        Matrix ret;
        ret.d[0][0] = ((d[0][0]*r.d[0][0]) % MOD + (d[0][1]*r.d[1][0]) % MOD) % MOD;
        ret.d[0][1] = ((d[0][0]*r.d[0][1]) % MOD + (d[0][1]*r.d[1][1]) % MOD) % MOD;
        ret.d[1][0] = ((d[1][0]*r.d[0][0]) % MOD + (d[1][1]*r.d[1][0]) % MOD) % MOD;
        ret.d[1][1] = ((d[1][0]*r.d[0][1]) % MOD + (d[1][1]*r.d[1][1]) % MOD) % MOD;
        return ret;
    }
};

Matrix expmod(Matrix m, ull n) {
    if (n == 0) return {{{1,0},{0,1}}};
    else if (n == 1) return m;
    else if (n % 2 == 0) return expmod(m*m,n/2);
    return m*expmod(m*m,n/2);
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ull n; cin >> n;
    Matrix a = {{{1,1},{1,0}}};
    Matrix ans = expmod(a,n);
    cout << ans.d[0][1] << '\n';


    return 0;
}
	

