#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
int p, k;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
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
int inverse(int x) {
    return modexp(x,M-2);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> p >> k;
    if (k == 0) {
        cout << modexp(p,p-1) << '\n';
        return 0;
    }
    if (k == 1) {
        cout << modexp(p,p) << '\n';
        return 0;
    }
    int ord = 1, cur = k;
    while (cur != 1) {
        cur = (1LL*cur*k) % p;
        ord++;
    }
    cout << modexp(p,(p-1)/ord) << '\n';
}

