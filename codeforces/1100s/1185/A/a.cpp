#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int a[3], d;
    cin >> a[0] >> a[1] >> a[2] >> d;
    sort(a,a+3);
    int ans = max(0,d-(a[1]-a[0])) + max(0,d-(a[2]-a[1]));
    cout << ans << '\n';
}

