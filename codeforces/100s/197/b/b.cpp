#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int a[maxn], b[maxn];
int n, m;

int main() {
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i <= m; i++) {
        cin >> b[i];
    }
    if (n > m) {
        if ((double)a[0]/b[0] < 0) cout << "-";
        cout << "Infinity\n";
    }
    else if (m > n) {
        cout << "0/1" << '\n';
    }
    else {
        int p = a[0];
        int q = b[0];
        int gc = abs(__gcd(p,q));
        if (q < 0) {
            p *= -1;
            q *= -1;
        }
        printf("%d/%d\n",p/gc,q/gc);
    }
}

