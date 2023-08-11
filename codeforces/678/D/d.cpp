#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
int A, B, X;
ll n;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int sub(int a, int b) {
    madd(a,M-b);
    return a;
}
int modexp(int a, ll b) {
    int res = 1;
    while (b > 0LL) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> A >> B >> n >> X;
    int ans = mult(modexp(A,n),X);
    if (A != 1) {
        int add = B;
        add = mult(add,sub(1,modexp(A,n)));
        add = mult(add,modexp(sub(1,A),M-2));
        madd(ans,add);
    }
    else {
        madd(ans,mult(B,n%M));
    }
    cout << ans << '\n';
}

