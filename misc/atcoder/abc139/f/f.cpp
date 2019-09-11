#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 105;
const ld PI = atan(1)*4;
int N;
struct Point
{
    int x, y;
};
vector<Point> pts;

ld modAngle(ld angle) {
    while (angle > PI) angle -= 2*PI;    
    while (angle < -PI) angle += 2*PI;
    return angle;
}

Point add(Point a, Point b) {
    return {a.x+b.x,a.y+b.y};
}

ld mag(Point a) {
    return sqrt(1LL*a.x*a.x + 1LL*a.y*a.y);
}

bool wrap(ld start, ld stop, ld curr) {
    if (start < stop) return curr >= stop || curr < start;    
    else return stop <= curr && curr < start;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int xi, yi; cin >> xi >> yi;
        if (xi == 0 && yi == 0) {
            continue;
        }
        else {
            pts.push_back({xi,yi});
        }
    }
    N = pts.size();
    sort(pts.begin(),pts.end(),[](auto a, auto b) {
            return atan2(a.x,a.y) < atan2(b.x,b.y);
            });
    for (int i = 0; i < N; i++) {
        pts.push_back(pts[i]);
    }
    /*
    for (auto p: pts) {
        cout << p.x << ' ' << p.y << ' ' << atan2(p.x,p.y) << '\n';
    }
    */
    ld res = 0;
    for (int i = 0; i < N; i++) {
        auto p = pts[i];
        Point sum = {0,0};
        ld best = 0;
        for (int j = i; j < min((int)pts.size(),i+N); j++) {
            sum = add(sum,pts[j]);
            best = max(best,mag(sum));
        }
        res = max(res,best);
    }
    cout << fixed << setprecision(25) << res << '\n';
}

