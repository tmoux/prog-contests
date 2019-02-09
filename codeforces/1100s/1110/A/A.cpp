#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int b, k; cin >> b >> k;
    bool r = 0;
    for (int i = 0; i < k - 1; i++) {
        int a; cin >> a;
        int s = (a&1) & (b&1);
        r ^= s;    
    }
    int a; cin >> a;
    r ^= (a&1);
    cout << (r ? "oDd" : "eVeN") << '\n';
    return 0;
}

