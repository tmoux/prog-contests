#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check(int a, int b, int x) {
    return a % b == 0 && a * b > x && a/b < x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x; cin >> x;
    for (int a = 1; a <= x; a++) {
        for (int b = a; b <= x; b++) {
            if (check(a,b,x)) {
                cout << a << ' ' << b << '\n';
                return 0;
            }
        }
    }
    cout << -1 << '\n';


    return 0;
}

