#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, x, y;
int a[maxn];

bool notRainy(int i) {
    for (int j = 1; j <= x; j++) {
        if (i-j < 1) continue;
        if (a[i-j] <= a[i]) return false;
    }
    for (int j = 1; j <= y; j++) {
        if (i+j > n) continue;
        if (a[i+j] <= a[i]) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> x >> y;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        if (notRainy(i)) {
            cout << i << '\n';
            return 0;
        }
    }
}

