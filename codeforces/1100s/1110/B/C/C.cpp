#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a; cin >> a;
    int ans = 0;
    for (int i = 1; i < a; i++) {
        ans = max(ans,__gcd(a^i,a&i));
    }
    cout << a << ": " << ans << '\n';


    return 0;
}

