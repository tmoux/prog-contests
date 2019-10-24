#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5+5;
int n, a[N];
ll pre[N];

ll sum(int l, int r) {
    return pre[r] - pre[l-1];
}

ll g(ll a, ll b, ll c, ll d) {
    return max(max(a,b),max(c,d)) - min(min(a,b),min(c,d));
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = a[i] + pre[i-1];
    }
    ll ans = 1e18;
    int o1 = 1, o2 = 3;
    for (int i = 2; i <= n-2; i++) {
        o2 = max(o2,i+1);
        while (o1+1 < i && abs(sum(o1+2,i)-sum(1,o1+1)) <
                           abs(sum(o1+1,i)-sum(1,o1)))
            o1++;
        while (o2+1 < n && abs(sum(i+1,o2+1)-sum(o2+2,n) <
                           abs(sum(i+1,o2)-sum(o2+1,n))))
            o2++;
        ans = min(ans,g(sum(1,o1),sum(o1+1,i),sum(i+1,o2),sum(o2+1,n)));
        printf("%d: o1 = %d, o2 = %d\n",i,o1,o2);
    }
    cout << ans << '\n';
}

