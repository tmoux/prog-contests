#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a1, a2, k1, k2;
    int n;
    cin >> a1 >> a2 >> k1 >> k2 >> n;
    int orig = n;
    if (k1 > k2) {
        swap(k1,k2);
        swap(a1,a2);
    }
    int mx = 0;
    for (int i = 0; i < a1; i++) {
        if (n >= k1) {
            n -= k1;
            mx++;
        }
    }
    for (int i = 0; i < a2; i++) {
        if (n >= k2) {
            n -= k2;
            mx++;
        }
    }
    //cout << mx << '\n';
    n = orig;
    //do min
    int mn = max(0,n - ((k1-1)*a1 + (k2-1)*a2));
    cout << mn << ' ' << mx << '\n';
}

