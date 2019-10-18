#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+9;
int n, m, k;

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int norm(int a) {
    while (a < 0) a += M;
    while (a >= M) a -= M;
    return a;
}

int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    int numWrong = n-m;
    int numPeriods = min(m/(k-1),numWrong);
    m -= numPeriods*(k-1);
    numWrong -= numPeriods;
    int numDoubles = m/k;
    int leftOver = m - numDoubles*k;

    int ans = mult(k,norm(modexp(2,numDoubles+1)-2));
    ans += leftOver;
    ans %= M;
    ans += mult(numPeriods,k-1);
    ans %= M;
    cout << ans << '\n';
}

