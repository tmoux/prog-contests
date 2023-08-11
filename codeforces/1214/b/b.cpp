#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int b, g, n; cin >> b >> g >> n;
    int boys = n, girls = 0;
    int ans = 0;
    while (boys >= 0) {
        if (boys <= b && girls <= g) {
            ans++;
        }
        boys--;
        girls++;
    }
    cout << ans << '\n';
}

