#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[maxn];
ll pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += (a[i])%2;
        sum %= 2;
    }
    sort(a,a+n);
    if (sum == 1) {
        cout << "NO\n";
        return 0;
    }
    else {
        ll s = 0;
        for (int i = 0; i < n-1; i++) {
            s += a[i];
        }
        cout << ((s >= a[n-1]) ? "YES" : "NO") << '\n';
    }
}

