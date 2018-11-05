#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, q;
struct Line
{
    int m, b;
    double intersect(const Line& r) { //returns x coordinate of intersection
        assert(m != r.m);
        return (double)(r.b-b)/(double)(m-r.m);
    }
    bool comp(Line& l1, Line& l2) {
        double x1 = l1.intersect(l2);
        double x2 = intersect(l2);
        return x2 <= x1; //true --> pop off l2    
    }
    bool operator<(const Line& l1) {
        return m > l1.m;
    }
    int eval(int x) {
        return m*x+b;
    }
};

int answer(int x, vector<Line>& hull, int lo, int hi) {
    if (hull.size() == 1) return hull.front().eval(x);
    if (lo == hi) return hull[lo].eval(x);
    if (x <= hull[lo].intersect(hull[lo+1])) return hull[lo].eval(x);
    if (x >= hull[hi].intersect(hull[hi-1])) return hull[hi].eval(x);
    int m = (lo+hi)/2;
    int x1 = hull[m].intersect(hull[m-1]);
    int x2 = hull[m].intersect(hull[m+1]);
    if (x1 <= x && x <= x2) return hull[m].eval(x);
    if (x < x1) return answer(x,hull,lo,m);
    else return answer(x,hull,m,hi);
    /*
    int res = 987654321;
    for (Line& l: hull) {
        res = min(res,l.eval(x));
    }
    return res;
    */
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    map<int,int> mp; //minimum b for the slope
    for (int i = 0; i < n; i++) {
        int m, b; cin >> m >> b;
        if (!mp.count(m)) mp[m] = b;
        else mp[m] = min(mp[m],b);
    }
    vector<Line> lines;
    for (auto& p: mp) {
        lines.push_back({p.first,p.second});
    }
    sort(lines.begin(),lines.end());
    vector<Line> hull;
    for (int i = 0; i < lines.size(); i++) {
        while (hull.size() >= 2) {
            Line& l1 = hull[hull.size()-2];
            Line& l2 = hull[hull.size()-1];
            if (lines[i].comp(l1,l2)) {
                hull.pop_back();
            }
            else {
                break;
            }
        }
        hull.push_back(lines[i]);
    }
    while (q--) {
        int x; cin >> x;
        int ans = answer(x,hull,0,hull.size()-1);
        cout << ans << '\n';
    }
    /*
    cout << hull.size() << '\n';
    for (Line l: hull) {
        cout << l.m << ' ' << l.b << '\n';
    }
    */


    return 0;
}

