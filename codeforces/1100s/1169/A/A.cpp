#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, a, x, b, y;
    cin >> n >> a >> x >> b >> y;
    bool poss = false;
    while (true) {
        a++;
        if (a == n+1) a = 1;
        b--;
        if (b == 0) b = n;
        if (a == b) {
            poss = true;
            break;
        }
        if (a == x || b == y) break;
    }
    cout << (poss ? "YES" : "NO") << '\n';
}

