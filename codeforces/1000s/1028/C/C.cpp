#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
struct Rect {
    int x1, y1, x2, y2;
} recs[150000];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    multiset<int> lx, rx, ly, ry;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> recs[i].x1 >> recs[i].y1 >> recs[i].x2 >> recs[i].y2;
        x1 = recs[i].x1;
        y1 = recs[i].y1;
        x2 = recs[i].x2;
        y2 = recs[i].y2;
        lx.insert(x1);
        rx.insert(x2);
        ly.insert(y1);
        ry.insert(y2);
    }

    pair<int,int> ans = {-1,-1};
    for (int i = 0; i < n; i++) {
        lx.erase(lx.find(recs[i].x1));
        rx.erase(rx.find(recs[i].x2));
        ly.erase(ly.find(recs[i].y1));
        ry.erase(ry.find(recs[i].y2));
        if ((*lx.rbegin()) <= (*rx.begin()) && (*ly.rbegin()) <= (*ry.begin())) {
            ans = {*lx.rbegin(),*ly.rbegin()};
            break;
        }
        lx.insert(recs[i].x1);
        rx.insert(recs[i].x2);
        ly.insert(recs[i].y1);
        ry.insert(recs[i].y2);
    }

    cout << ans.first << ' ' << ans.second << '\n';

    return 0;
}
	

