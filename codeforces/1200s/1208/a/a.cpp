#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//a,b,a^b,a,b,

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b, n; cin >> a >> b >> n;
        if (n % 3 == 0) {
            cout << a << '\n';
        }
        else if (n % 3 == 1) {
            cout << b << '\n';
        }
        else {
            cout << (a^b) << '\n';
        }
    }

}

