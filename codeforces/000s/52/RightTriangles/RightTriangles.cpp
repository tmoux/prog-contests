#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct vCount
{
	int horiz, vert;
};

const int maxn = 1005;
int n, m;
bool grid[maxn][maxn];

vCount counts[maxn][maxn];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c; cin >> c;
			grid[i][j] = (c == '*');
		}
	}
	//fill in count array
	//horiz
	for (int i = 0; i < n; i++) {
		int num = 0;
		for (int j = 0; j < m; j++) {
			if (grid[i][j]) {
				num++;
			}
		}
		num--;
		for (int j = 0; j < m; j++) {
			counts[i][j].horiz = num;
		}
	}
	//vert
	for (int i = 0; i < m; i++) {
		int num = 0;
		for (int j = 0; j < n; j++) {
			if (grid[j][i]) {
				num++;
			}
		}
		num--;
		for (int j = 0; j < n; j++) {
			counts[j][i].vert = num;
		}
	}

	//calculation
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j]) {
				vCount c = counts[i][j];
				
				ll plus = c.vert*c.horiz;
				ans += plus;
				//printf("%d %d %d %d %d %d : %d\n",i,j,c.vert,c.horiz,c.diag1,c.diag2,plus);
			}
		}
	}
	cout << ans << '\n';
	
	return 0;
}