#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a-= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

int n;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int ans = 0;
        if (n-i-1 > 0) {
            int add = n-i-1;
            add = mult(add,mult(10,81));
            add = mult(add,modexp(10,n-i-2));
            madd(ans,add);
        }
        int add = mult(2*10*9,modexp(10,n-i-1));
        madd(ans,add);
        cout << ans << ' ';
    }
    //i=n
    cout << 10 << '\n';
}

