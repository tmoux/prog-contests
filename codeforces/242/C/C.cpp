#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n;
set<pair<int,int>> s, seen;

vector<pair<int,int>> nxt(pair<int,int> p) {
    vector<pair<int,int>> res;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            res.push_back({p.first+i,p.second+j});
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x0, y0, x1, y1; cin >> x0 >> y0 >> x1 >> y1;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int r, a, b; cin >> r >> a >> b;
        for (int j = a; j <= b; j++) {
            s.insert({r,j});
        }
    }
    queue<pair<pair<int,int>,int>> q;
    q.push({{x0,y0},0});
    seen.insert({x0,y0});
    while (!q.empty()) {
        auto f = q.front(); q.pop();
        int dist = f.second;
        pair<int,int> p = f.first;
        //cout << p.first << ' ' << p.second << '\n';
        if (p.first == x1 && p.second == y1) {
            cout << dist << '\n';
            return 0;
        }
        for (pair<int,int> u: nxt(p)) {
            if (seen.count(u) || !s.count(u)) continue;
            seen.insert(u);
            q.push({u,dist+1});
        }
    }
    cout << -1 << '\n';

    return 0;
}

