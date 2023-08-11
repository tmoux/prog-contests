#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool grid[1005][1005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int ax, ay, bx, by, cx, cy; cin >> ax >> ay >> bx >> by >> cx >> cy;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == ax || j == ay || abs(i-ax) == abs(j-ay)) {
                grid[i][j] = true;    
            }
        }
    }
    queue<pair<int,int>> q;
    q.push({bx,by});
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        grid[x][y] = true;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (1 <= x+i && x+i <= n && 1 <= y+j && y+j <= n && !grid[x+i][y+j]) {
                    grid[x+i][y+j] = true;
                    q.push({x+i,y+j});
                }
            }
        }
        q.pop();
    }
    cout << (grid[cx][cy] ? "YES" : "NO") << '\n';

    return 0;
}

