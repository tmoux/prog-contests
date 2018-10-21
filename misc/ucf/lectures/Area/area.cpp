#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Point {int x, y;};

void solve(int n) {
    vector<Point> ps(n);
    Point minp = {0,99999}; int idx;
    for (int i = 0; i < n; i++) { 
        cin >> ps[i].x >> ps[i].y;
        if (ps[i].y < minp.y || (ps[i].y == minp.y && ps[i].x < minp.x) {
            minp = ps[i];
            idx = i;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        solve(n);
    }

    return 0;
}
	

