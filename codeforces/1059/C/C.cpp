#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int c = 1;
    while (n > 3) {
        for (int i = 0; i < (n+1)/2; i++) {
            cout << c << ' ';
        }
        c *= 2;
        n /= 2;
    }
    if (n == 1) {
        cout << c << '\n';
    }
    else if (n == 2) {
        cout << c << ' ' << 2*c << '\n';
    }
    else {
        cout << c << ' ' << c << ' ' << 3*c << '\n';
    }

    return 0;
}

