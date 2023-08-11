#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n, l, r;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> l >> r;
    int mn = 0;
    for (int i = 0; i < l; i++) {
        mn += (1<<i);
    }
    for (int i = 0; i < n-l; i++) {
        mn += 1;
    }
    int mx = 0;
    for (int i = 0; i < r; i++) {
        mx += (1<<i);
    }
    for (int i = 0; i < n-r; i++) {
        mx += (1<<(r-1));
    }
    cout << mn << ' ' << mx << '\n';
}

