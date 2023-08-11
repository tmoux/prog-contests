#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 53;
int n, m;
pair<int,int> target[maxn];
struct Sq { int x, y, id; } curr[maxn];
vector<tuple<int,int,int,int>> ans;
void addans(int x1, int y1, int x2, int y2) {
    ans.push_back(make_tuple(x1,y1,x2,y2));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> curr[i].x >> curr[i].y;
        curr[i].id = i;
    }
    for (int i = 0; i < m; i++) {
        cin >> target[i].first >> target[i].second;
    }
    sort(curr,curr+m,[] (Sq& lh, Sq& rh) { return lh.x < rh.x; });
    for (int i = 0; i < n; i++) {
        
    }

    return 0;
}
	

