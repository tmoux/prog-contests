#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const double eps = 1e-9;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x, y; cin >> x >> y;
    double dist = sqrt(x*x+y*y);
    if (dist-(int)dist <= eps) {
        //integral point
        cout << "black\n";
        return 0;
    }
    bool d = ((int)dist) % 2 == 0;
    bool c = (x < 0) == (y < 0);
    /*
    cout << "dist = " << dist << '\n';
    cout << "d = " << d << '\n';
    cout << "c = " << c << '\n';
    */
    cout << ((c^d) ? "white" : "black") << '\n';
}

