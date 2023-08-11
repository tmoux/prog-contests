#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Point {
    int x, y;

    Point operator-(const Point& rhs) const {
        return {x-rhs.x,y-rhs.y};
    }
};

int cross(Point a, Point b) {
    return a.x*b.y-a.y*b.x;
}

Point a[4], b[4];    


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 0; i < 4; i++) {
        cin >> a[i].x >> a[i].y;
    }
    for (int i = 0; i < 4; i++) {
        cin >> b[i].x >> b[i].y;
    }
    cout << cross({0,1},{1,0}) << '\n';
    
    

    return 0;
}
	

