#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        int minX = -100000;
        int maxX = 100000;
        int minY = -100000;
        int maxY = 100000;
        for (int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            int f; 
            cin >> f; //move left
            if (f == 0) {
                minX = max(minX,x);
            }
            cin >> f; //move up
            if (f == 0) {
                maxY = min(maxY,y);
            }
            cin >> f; //move right
            if (f == 0) {
                maxX = min(maxX,x);
            }
            cin >> f; //move down
            if (f == 0) {
                minY = max(minY,y);
            }
        }
        if (minX > maxX || minY > maxY) {
            cout << 0 << '\n';
        }
        else {
            cout << 1 << ' ' << minX << ' ' << minY << '\n';
        }
    }

}

