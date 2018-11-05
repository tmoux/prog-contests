#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; string s; cin >> n >> s;
    int k = s.size();
    ll r = 1;
    for (; n > 0; n -= k) {
        r *= n;
    }
    cout << r << '\n';

    return 0;
}

