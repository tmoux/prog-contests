#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, p, k;
int a[maxn];
int sqr(int x) {
    return (1LL*x*x) % p;
}

int f(int x) {
    return (sqr(sqr(x)) - ((1LL*k*x)%p) + p) % p;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> p >> k;
    map<int,int> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans += s[f(a[i])];
        //cout << a[i] << ": " << f(a[i]) << '\n';
        s[f(a[i])]++;
    }
    cout << ans << '\n';
}

