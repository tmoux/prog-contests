#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
const int INF = 2e9;
int n;
struct Point {
    int x, y;
    bool operator==(const Point& b) {
        return x == b.x && y == b.y;
    }
} pts[maxn];

void amin(int& a, int b) {
    a = min(a,b);
}
void amax(int& a, int b) {
    a = max(a,b);
}

int dist(Point& a, Point& b) {
    return abs(a.x-b.x) + abs(a.y-b.y);
}

int perim(Point& a, Point& b, Point& c) {
    return dist(a,b) + dist(a,c) + dist(b,c);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int mnX = INF, mxX = -INF, mnY = INF, mxY = -INF;
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
        amin(mnX,pts[i].x);
        amin(mnY,pts[i].y);
        amax(mxX,pts[i].x);
        amax(mxY,pts[i].y);
    }
    int ans = 2*(mxX-mnX+mxY-mnY);
    auto sortx = [](Point& a, Point& b) { return a.x < b.x; };
    auto sorty = [](Point& a, Point& b) { return a.y < b.y; };
    sort(pts,pts+n,sortx);
    vector<Point> extremes;
    set<int> s;
    for (int i = 0; i < n; i++) {
        if (pts[i].x > mnX) break;
        s.insert(pts[i].y);
    }
    extremes.push_back({mnX,*s.begin()});
    extremes.push_back({mnX,*s.rbegin()});
    s.clear();
    for (int i = n - 1; i >= 0; i--) {
        if (pts[i].x < mxX) break;
        s.insert(pts[i].y);
    }
    extremes.push_back({mxX,*s.begin()});
    extremes.push_back({mxX,*s.rbegin()});
    sort(pts,pts+n,sorty);
    /*
    for (int i = 0; i < n; i++) {
        cout << pts[i].x << ' ' << pts[i].y << '\n';
    }
    */
    s.clear();
    for (int i = 0; i < n; i++) {
        if (pts[i].y > mnY) break;
        s.insert(pts[i].x);
    }
    extremes.push_back({*s.begin(),mnY});
    extremes.push_back({*s.rbegin(),mnY});
    s.clear();
    for (int i = n - 1; i >= 0; i--) {
        if (pts[i].y < mxY) break;
        s.insert(pts[i].x);
    }
    extremes.push_back({*s.begin(),mxY});
    extremes.push_back({*s.rbegin(),mxY});

    int mx3 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < extremes.size(); j++) {
            for (int k = j + 1; k < extremes.size(); k++) {
                if (pts[i] == extremes[j] || pts[i] == extremes[k] || extremes[j] == extremes[k]) continue;
                int p = perim(pts[i],extremes[j],extremes[k]);
                amax(mx3,p);    
                /*
                cout << pts[i].x << ' ' << pts[i].y << '\n';
                cout << extremes[j].x << ' ' << extremes[j].y << '\n';
                cout << extremes[k].x << ' ' << extremes[k].y << '\n';
                cout << p << "\n\n";
                */
            }
        }
    }
    cout << mx3 << ' ';
    for (int i = 4; i <= n; i++) {
        cout << ans << ' ';
    }

    return 0;
}

