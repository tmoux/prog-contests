#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int a[100000];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int i = 0;
    int days = 0;
    while (i <= n) {
        i++;
        if (i > n) break;
        int mx = a[i];
        while (i < mx) {
            i++;
            mx = max(mx,a[i]);
        }
        days++;
    }
    cout << days << '\n';
}

