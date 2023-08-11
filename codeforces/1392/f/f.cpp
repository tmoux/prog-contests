#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; scanf("%d",&n);
    vector<ll> a(n);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld",&a[i]);
        sum += a[i];
    }
    vector<ll> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = i+1;
        sum -= ans[i];
    }
    ll add = sum/n;
    ll extra = sum % n;
    for (int i = 0; i < n; i++) {
        ans[i] += add;
        if (i < extra) ans[i]++;
    }
    for (int i = 0; i < n; i++) {
        printf("%lld ",ans[i]);
    }
}
