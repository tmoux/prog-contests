#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 2505;
int n;
struct Point
{
    int x, y;
    ld ang;
};
const ld pi = atan((ld)1.0)*4;

vector<Point> points;

ll ch[maxn][5];

ll ch4(int x) {
    return ch[x][4];
}

ll ch3(int x) {
    return ch[x][3];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i <= n; i++) {
        ch[i][0] = 1;
        for (int j = 1; j <= min(i,4); j++) {
            ch[i][j] += ch[i-1][j-1];
            ch[i][j] += ch[i-1][j];
        }
    }
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.push_back({x,y});
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        //cout << i << "\n";
        vector<Point> v;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            v.push_back({points[j].x-points[i].x,points[j].y-points[i].y});
            v.back().ang = atan2((ld)v.back().y,(ld)v.back().x);
        }
        sort(v.begin(),v.end(),[](auto a, auto b) {
                return a.ang < b.ang;
                });
        for (int j = 0; j < n-1; j++) {
            v.push_back(v[j]);
            v.back().ang += 2*pi;
        }
        /*
        for (int j = 0; j < v.size(); j++) {
            cout << j << ": " << v[j].x << ' ' << v[j].y << " " << v[j].ang << '\n';
        }
        */
        int pt = 0;        
        ll add = ch4(n-1);
        for (int j = 0; j < n-1; j++) {
            while (pt < v.size() && v[pt].ang <= v[j].ang+pi) pt++;
            //cout << j << ' ' << pt << ": " << (pt-j-1) << '\n';
            add -= ch3(pt-j-1);
        }
        //cout << "adding " << add << '\n';
        ans += add;
    }
    cout << ans << '\n';
}

