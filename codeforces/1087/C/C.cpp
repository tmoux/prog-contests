#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point
{
    int x, y;
    bool operator<(const Point& rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};

void append(Point q, Point p, set<Point>& r) {
    for (int i = p.x; i != q.x; (p.x<q.x?i++:i--)) {
        r.insert({i,p.y});    
    }
    for (int i = p.y; i != q.y; (p.y<q.y?i++:i--)) {
        r.insert({q.x,i});
    }
    r.insert(q);
}

void append2(Point q, Point p, set<Point>& r) {
    for (int i = p.y; i != q.y; (p.y<q.y?i++:i--)) {
        r.insert({p.x,i});        
    }
    for (int i = p.x; i != q.x; (p.x<q.x?i++:i--)) {
        r.insert({i,q.y});
    }
    r.insert(q);
}

Point A, B, C;
set<Point> get(Point p) {
    set<Point> res;
    for (Point q: {A,B,C}) {
        append(q,p,res);
    }
    set<Point> res2;
    for (Point q: {A,B,C}) {
        append(q,p,res2);
    }
    return res.size()<res2.size()?res:res2;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
    int xc = (A.x+B.x+C.x)/3;
    int yc = (A.y+B.y+C.y)/3;
    Point centroid = {xc,yc};
    set<Point> ans;
    int sz = 999999999;
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            Point d = {xc+i,yc+j};
            if (d.x < 0 || d.x > 1000 || d.y < 0 || d.y > 1000) continue;
            set<Point> aa = get(d);
            if (aa.size() < sz) {
                sz = aa.size();
                ans = aa;
            }
        }
    }
    for (Point d: {A,B,C}) {
        set<Point> aa = get(d);
        if (aa.size() < sz) {
            sz = aa.size();
            ans = aa;
        }
    }
    //output
    cout << sz << '\n';
    for (Point p: ans) {
        cout << p.x << ' ' << p.y << '\n';
    }

    return 0;
}

