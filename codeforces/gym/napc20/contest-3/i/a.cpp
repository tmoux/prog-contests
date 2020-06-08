#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 1e5+5, maxx = 505;
int n, q;
ld grid[maxx][maxx];
vector<pair<int,ld>> V[maxx];

struct vec2
{
    ld x, y;
    vec2() {}
    vec2(ld _x, ld _y) {
        x = _x;
        y = _y;
    }
    vec2 operator-(vec2 b) {
        return {x-b.x,y-b.y};
    }
    vec2 operator+(vec2 b) {
        return {x+b.x,y+b.y};
    }
    vec2 scale(ld k) {
        return {k*x,k*y};
    }
};

ld dot(vec2 a, vec2 b) {
    return a.x*b.x+a.y*b.y;
}

ld min_dist(vec2 v, vec2 w, vec2 p) { //distance to line seg squared
    ld l2 = dot(v-w,v-w);
    ld t = max((ld)0.0,min((ld)1.0,dot(p-v,w-v)/l2));
    vec2 proj = v + (w-v).scale(t);
    return dot(p-proj,p-proj);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i <= 500; i++) {
        for (int j = 0; j <= 500; j++) {
            grid[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        int x, y; ld r; cin >> x >> y >> r;
        grid[x][y] = r*r;
        V[x].push_back({y,r*r});
    }
    for (int i = 1; i <= 500; i++) {
        sort(V[i].begin(),V[i].end());
    }
    cin >> q;
    while (q--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) {
            swap(x1,x2);
            swap(y1,y2);
        }
        vec2 v = {(ld)x1,(ld)y1}, w = {(ld)x2,(ld)y2};
        int cnt = 0;
        if (x1 == x2) {
            for (int y = min(y1,y2); y <= max(y1,y2); y++) {
                if (grid[x1][y] > 0) {
                    cnt++;
                }
            }
        }
        else {
            for (int x = x1; x <= x2; x++) {
                int y_min = (int)y1 + (int)(ld)(x-1-x1)*(ld)(y2-y1)/(ld)(x2-x1);
                int y_max = (int)y1 + (int)(ld)(x+1-x1)*(ld)(y2-y1)/(ld)(x2-x1);
                if (y_min > y_max) swap(y_min,y_max);
                //cout << y_min << ' ' << y_max << endl;
                for (int y = max(0,y_min-1); y <= min(y_max+1,500); y++) {
                //for (int y = 0; y <= 500; y++) {
                    if (grid[x][y] > 0) {
                        if (min_dist(v,w,vec2(x,y)) < grid[x][y]) {
                            cnt++;
                        }
                    }
                }
                /*
                ld y = y1 + (ld)(x-x1)*(ld)(y2-y1)/(ld)(x2-x1);
                int y_f = (int)floor(y);
                auto it = upper_bound(V[x].begin(),V[x].end(),make_pair(y_f,(ld)1));
                auto it2 = upper_bound(V[x].begin(),V[x].end(),make_pair(y_f,(ld)1));
                if (it != V[x].end()) {
                    ld d = min_dist(v,w,vec2(x,it->first));
                    if (d < it->second) cnt++;
                }
                if (it2 != V[x].end() && (it2->first != it->first)) {
                    ld d = min_dist(v,w,vec2(x,it2->first));
                    if (d < it2->second) cnt++;
                }
                if (it2 != V[x].end()) {
                    ++it2;
                    if (it2 != V[x].end() && (it2->first != it->first)) {
                        ld d = min_dist(v,w,vec2(x,it2->first));
                        if (d < it2->second) cnt++;
                    }
                }
                if (it != V[x].begin()) {
                    --it;
                    ld d = min_dist(v,w,vec2(x,it->first));
                    if (d < it->second) cnt++;
                }
                */
            }
        }
        cout << cnt << '\n';
    }
    //cout << min_dist(vec2(2,1),vec2(2,4),vec2(3,6)) << endl;
    //cout << min_dist(vec2(0,0),vec2(-3,3),vec2(5,0)) << endl;
}
