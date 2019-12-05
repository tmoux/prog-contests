#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[maxn];
const int M = 1e9+7;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int r = -1, b = -1, g = -1;
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        if (r == a[i]-1) cnt++;
        if (g == a[i]-1) cnt++;
        if (b == a[i]-1) cnt++;
        //cout << i << ": " << cnt << '\n';
        ans = mult(ans,cnt);
        if (r == a[i]-1) r++;
        else if (b == a[i]-1) b++;
        else if (g == a[i]-1) g++;
    }
    cout << ans << '\n';
}

