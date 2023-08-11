#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5, M = 1e9+7;;
int n, x[maxn];

int mult(int a, int b) {
    return (1LL*a*b) % M;
}
void madd(int& a, int b) {
    a = (a+b) % M;
}
void msub(int& a, int b) {
    a = (a-b+M) % M;
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
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    sort(x+1,x+n+1);
    int tot = 0;
    for (int i = 2; i <= n; i++) {
        madd(tot,mult(x[i],modexp(2,i-2)));
    }
    int ans = 0;
    for (int i = 1, j = n-1; i < n; i++, j--) {
        int add = tot;
        msub(add,mult(x[i],modexp(2,j)-1+M)%M);
        madd(ans,add);
        /*
        cout << i << ": " << tot << endl;
        cout << add << endl;
        */
        msub(tot,x[i+1]);
        tot = mult(tot,inverse(2));
    }
    cout << ans << endl;
}
