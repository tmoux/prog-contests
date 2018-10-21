#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Vec2
{
    int x, y;
    Vec2 operator+(const Vec2& rhs) const{
        return {x+rhs.x,y+rhs.y};
    }
    Vec2 operator-(const Vec2& rhs) const{
        return {x-rhs.x,y-rhs.y};
    }
};
struct Square
{
    Vec2 points[4];
    pair<Vec2,Vec2> sides[4];
    Square() {}
    Square(pair<int,int> p[4]) {
        for (int i = 0; i < 4; i++) {
            points[i].x = p[i].first;
            points[i].y = p[i].second;
        }
        for (int i = 0; i < 4; i++) {
            sides[i] = {points[i],points[(i+1)%4]};
        }
    }
};

int cross(const Vec2& lhs, const Vec2& rhs) {
    return lhs.x*rhs.y - lhs.y*rhs.x;
}
bool isIntersect(const pair<Vec2,Vec2>& s1, const pair<Vec2,Vec2>& s2) {
    Vec2 v1 = s1.first-s1.second, v2 = s2.first-s2.second;
    int c1 = cross(v1,s2.first), c2 = cross(v1,s2.second);
    bool parallel = c1 == 0 && c2 == 0;
    bool in1 = c1 != c2;
    int c3 = cross(v2,s1.first), c4 = cross(v2,s1.second);
    bool in2 = c3 != c4;
    cout << parallel << ' ' << in2 << ' ' << in2 << '\n';
    return parallel || in1 || in2;    
}



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    Square sqs[2];
    pair<int,int> p[4];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            int x, y; cin >> x >> y;
            p[j].first = x;
            p[j].second = y;
        }
        sqs[i] = Square(p);
    }

    pair<Vec2,Vec2> s1 = {{0,0},{0,5}}, s2 = {{1,4},{5,0}};
    cout << isIntersect(s1,s2) << '\n';

    return 0;
}
	

