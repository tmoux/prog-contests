#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, sx, sy;
pair<int,int> p[maxn];
int c[4];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    cin >> sx >> sy;
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
        p[i].first -= sx;
        p[i].second -= sy;
        int x = p[i].first;
        int y = p[i].second;
        if (x > 0) c[0]++;
        if (y > 0) c[1]++;
        if (x < 0) c[2]++;
        if (y < 0) c[3]++;
    }
    int mx = max(max(c[0],c[1]),max(c[2],c[3]));
    cout << mx << '\n';
    if (c[0] == mx) {
        cout << sx + 1 << ' ' << sy << '\n';
    }
    else if (c[1] == mx) {
        cout << sx << ' ' << sy+1 << '\n';
    }
    else if (c[2] == mx) {
        cout << sx - 1 << ' ' << sy << '\n';
    }
    else if (c[3] == mx) {
        cout << sx << ' ' << sy-1 << '\n';
    }
}

