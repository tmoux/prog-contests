#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int x, y, z; cin >> x >> y >> z;
    int c = x - y;
    int c1 = c - z;
    int c2 = c + z;
    if (c1 == 0 && c2 == 0) {
        cout << "0\n";
    }
    else if (c1 < 0 && c2 < 0) {
        cout << "-\n";
    }
    else if (c1 > 0 && c2 > 0) {
        cout << "+\n";
    }
    else {
        cout << "?\n";
    }
}

