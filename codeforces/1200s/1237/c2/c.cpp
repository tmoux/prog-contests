#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 50005;
int n;
struct Point
{
    ll x, y, z;
    int id;
} pts[maxn];

bool use[maxn];

ll sqr(ll x) {
    return x*x;
}

ll dist(Point a, Point b) {
    //return min(abs(a.x-b.x),min(abs(a.y-b.y),abs(a.z-b.z)));
    return sqr(a.x-b.x) + sqr(a.y-b.y) + sqr(a.z-b.z);
}

auto cmpX = [](Point a, Point b) { 
    if (a.x != b.x) return a.x < b.x;
    return a.id < b.id;
};

auto cmpY = [](Point a, Point b) { 
    if (a.y != b.y) return a.y < b.y;
    return a.id < b.id;
};
auto cmpZ = [](Point a, Point b) { 
    if (a.z < b.z) return a.z < b.z;
    return a.id < b.id;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<Point> p;
    map<int,vector<Point>> slice;
    for (int i = 1; i <= n; i++) {
        cin >> pts[i].x >> pts[i].y >> pts[i].z;
        pts[i].id = i;
        slice[pts[i].x].push_back(pts[i]);
    }
    vector<pair<int,int>> ans;
    for (auto& pa: slice) {
        vector<Point>& v = pa.second;
        sort(v.begin(),v.end(),[](auto a, auto b) {
                if (a.y != b.y) return a.y < b.y;
                return a.z < b.z;
                });
        for (int i = 0; i < v.size()-1; i++) {
            if (use[v[i].id] || use[v[i+1].id]) continue;
            if (v[i].y == v[i+1].y) {
                use[v[i].id] = true;
                use[v[i+1].id] = true;
                ans.push_back({v[i].id,v[i+1].id});
                i++;
            }
        }
        vector<Point> vv;
        for (int i = 0; i < v.size(); i++) {
            if (!use[v[i].id]) {
                vv.push_back(v[i]);
            }
        }
        if (!vv.empty()) {
            for (int i = 0; i < (int)vv.size()-1; i += 2) {
                use[vv[i].id] = true;
                use[vv[i+1].id] = true;
                ans.push_back({vv[i].id,vv[i+1].id});
            }
        }
        for (int i = 0; i < vv.size(); i++) {
            if (!use[vv[i].id]) {
                p.push_back(vv[i]);
            }
        }
    }
    for (int i = 0; i < p.size(); i += 2) {
        ans.push_back({p[i].id,p[i+1].id});
    }
    //output
    for (auto pp: ans) {
        cout << pp.first << ' ' << pp.second << '\n';
    }
}

