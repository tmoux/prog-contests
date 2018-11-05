#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
map<int,vector<pair<int,int>>> ans;

void place(int c, int x, int y) {
    ans[c].push_back({x,y});
}

set<int> send[maxn], receive[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if (a > b) swap(a,b);
        send[a].insert(b);
        receive[b].insert(a);
    }
    for (int i = 1; i <= n; i++) {
        int xoff = i*1000, yoff = i*1000;
        place(i,xoff,yoff);
        for (int j: send[i]) {
            place(i,xoff+j,yoff);
            place(i,xoff+j,j*1000+i);
        }
        for (int j: receive[i]) {
            place(i,xoff,yoff+j);
        }
    }

    //output
    for (int i = 1; i <= n; i++) {
        vector<pair<int,int>>& v = ans[i];
        cout << v.size() << '\n';
        for (auto& p: v) {
            cout << p.first << ' ' << p.second << '\n';
        }
    }

    return 0;
}

