#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)
//dumbest problem I've seen in a while
//Pointless implementation. boooo. other than that ABCE were fine. 

const int maxn = 1e5+5;
int n, m, k;

vector<int> rows[maxn], cols[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    set<pair<int,int>> s;
    for (int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        rows[x].push_back(y);
        cols[y].push_back(x);
        s.insert({x,y});
    }
    for (int i = 1; i <= n; i++) {
        sort(all(rows[i]));
    }
    for (int i = 1; i <= m; i++) {
        sort(all(cols[i]));
    }
    int r_min = 0, r_max = n+1, c_min = 0, c_max = m+1;
    int x = 1, y = 1;
    int dir = 0;
    ll total = 1;
    int pt = 0;
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s.count({i,j})) cout << 1 << ' ';
            else cout << 0 << ' ';
        }
        cout << '\n';
    }
    */
    int bad = 0;
    while (true) {
        /*
        pt++;
        if (pt > 10) break;
        cout << x << ' ' << y << '\n';
        printf("r_min = %d\n",r_min);
        */
        int nx = x, ny = y;
        //cout << x << ' ' << y << endl;
        if (dir == 0) {
            //right
            ny = c_max - 1;
            auto it = upper_bound(all(rows[x]),y);
            if (it != rows[x].end()) ny = min(ny,*it-1);
            r_min = nx;
        }
        else if (dir == 1) {
            //down
            nx = r_max - 1;
            auto it = upper_bound(all(cols[y]),x);
            if (it != cols[y].end()) nx = min(nx,*it-1);
            c_max = ny;
        }
        else if (dir == 2) {
            //left
            ny = c_min + 1;
            auto it = lower_bound(all(rows[x]),y);
            if (it != rows[x].begin()) {
                --it;
                ny = max(ny,*it+1);
            }
            r_max = nx;
        }
        else if (dir == 3) {
            //up
            nx = r_min + 1;
            auto it = lower_bound(all(cols[y]),x);
            if (it != cols[y].begin()) {
                --it;
                nx = max(nx,*it+1);
            }
            c_min = ny;
        }
        int add = abs(nx-x) + abs(ny-y);
        if (add == 0) {
            break;
        }
        else {
            total += add;
            x = nx;
            y = ny;
            dir = (dir+1) % 4;
        }
    }
    int cnt = 0;
    for (int j = 1; j <= n; j++) {
        if (s.count({j,1})) break;
        cnt++;
    }
    if (cnt == 1LL*m*n-k) {
        cout << "Yes\n";
        return 0;
    }
    if (1LL*m*n - total == k) {
        cout << "Yes\n";
    }
    else cout << "No\n";
}
