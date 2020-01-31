#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+5;
int n, a[maxn];
int mu[maxn];
int cnt[maxn];
int num_div[maxn]; //# of array elements that divide i

void mobius_sieve() {
    mu[1] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 2*i; j < maxn; j += i) {
            mu[j] -= mu[i];
        }
    }
}

ll brute() {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (__gcd(a[i],a[j]) == 1) ans++;
        }
    }
    return ans;
}

ll ch3(ll x) {
    return x*(x-1)*(x-2)/6;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    mobius_sieve();
    for (int i = 1; i < maxn; i++) {
        for (int j = i; j < maxn; j += i) {
            num_div[i] += cnt[j];
        }
    }
    ll ans = 0;
    for (int d = 1; d < maxn; d++) {
        ans += mu[d]*ch3(num_div[d]);
    }
    cout << ans << '\n';
}

