#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
ll n, a[maxn], b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int l = 1, r = n;
    for (int i = 0; i < n/2; i++,l++,r--) {
        if (l == 1) {
            a[l] = 0;
            a[r] = b[i];
        }
        else {
            ll x = a[l-1];
            ll y = b[i] - x;
            if (y <= a[r+1]) {
                a[l] = x;
                a[r] = y;
            }
            else {
                y = a[r+1];
                x = b[i] - y;
                a[l] = x;
                a[r] = y;
            }
        }   
    }

    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }

    return 0;
}

