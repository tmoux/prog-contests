#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 505;
int n, m;
bool grid[maxn][maxn];
bool vis[maxn][maxn];

void floodfill(int x, int y) {
	vis[x][y] = true;
	if (!vis[x+1][y] && grid[x+1][y]) floodfill(x+1,y);
	if (!vis[x-1][y] && grid[x-1][y]) floodfill(x-1,y);
	if (!vis[x][y+1] && grid[x][y+1]) floodfill(x,y+1);
	if (!vis[x][y-1] && grid[x][y-1]) floodfill(x,y-1);
	vis[x+1][y] = true;
	vis[x-1][y] = true;
	vis[x][y-1] = true;
	vis[x][y+1] = true;
}

int countAdj(int x, int y) {
	return (grid[x][y+1] + grid[x][y-1] + grid[x-1][y] + grid[x+1][y]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
    	string s; cin >> s;
    	for (int j = 1; j <= m; j++) {
    		grid[i][j] = (s[j-1] == '.');
    	}
    }
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
   	if (x1 == x2 && y1 == y2) {
   		if (countAdj(x1,y1) >= 1) {
   			cout << "YES" << '\n';
   			return 0;
   		}
   		else {
   			cout << "NO\n";
   			return 0;
   		}
   	}
   	else if (abs(x1-x2) + abs(y1-y2) == 1) {
   		if (!grid[x2][y2] || countAdj(x2,y2) >= 1) {
   			cout << "YES" << '\n';
   			return 0;
   		}
   		else {
   			cout << "NO" << '\n';
   			return 0;
   		}
   	}
   	else {
   		floodfill(x1,y1);
   		if (vis[x2][y2]) {
   			if (!grid[x2][y2]) {
   				cout << "YES" << '\n';
   				return 0;
   			}
   			else if (countAdj(x2,y2) >= 2) {
   				cout << "YES" << '\n';
   				return 0;
   			}
   		}
   		cout << "NO" << '\n';
   	}

    return 0;
}