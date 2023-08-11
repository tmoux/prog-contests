#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, q;
int a[maxn];
int w[maxn];

int calc(int x) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += w[i]*abs(a[i]-(x+i-1));
    }
    return ans;
}

int bal(int x) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] < x+i-1) ans -= w[i];
        //else if (a[i] > x+i-1) ans += w[i];
        else ans += w[i];
    }
    return abs(ans);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = a[1]; i <= a[n]; i++) {
        cout << i << ": " << calc(i) << ' ' << bal(i) << endl;
    }
}

