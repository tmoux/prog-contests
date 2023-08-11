#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int minans = 2e9+9;
    for (int i = 1; i*i <= n; i++) {
        int r = i;
        int c = n/i;
        int rem = n - r*c;
        int need = r + c;
        if (rem > 0) need++;
        minans = min(minans,need);
    }
    cout << minans << '\n';

    return 0;
}

