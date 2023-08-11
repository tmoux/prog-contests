#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// the-reAl-lIsA-ching
//
// theRe_alL_is_aChing
//

const int maxn = 1e5+5, M = 1e9+7;
void madd(int& a, int b) {
    a = (a+b) % M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int n, bit[1000005], a[maxn];
void add(int i, int x) {
    for (; i <= 1000000; i += i & (-i))
        madd(bit[i],x);
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        madd(r,bit[i]);
    }
    return r;
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        int toAdd = (mult(a[i],sum(a[i])) + a[i]) % M;
        add(a[i],(sum(a[i]-1)-sum(a[i])+M)%M);
        add(a[i],toAdd);
        /*
        cout << sum(a[i]) << '\n';
        cout << i << ": " << toAdd << '\n';
        */
    }

    int ans = sum(1000000);
    cout << ans << '\n';
}

