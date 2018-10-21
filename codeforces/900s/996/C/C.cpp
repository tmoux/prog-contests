#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Move
{
	int i, r, c;
};

vector<Move> ans;
const int maxn = 52;
int grid[5][maxn];
//grid[i][j] = 0 means empty
int n, k;

pair<int,int> goClock(const pair<int,int>& p) {
	if (p.first == 2) {
		if (p.second == n) {
			return {3,n};
		}
		return {p.first,p.second+1};
	}
	else if (p.first == 3) {
		if (p.second == 1) {
			return {2,1};
		}
		return {p.first,p.second-1};
	}
}

pair<int,int> goCounter(const pair<int,int>& p) {
	if (p.first == 2) {
		if (p.second == 1) {
			return {3,1};
		}
		return {p.first,p.second-1};
	}
	else if (p.first == 3) {
		if (p.second == n) {
			return {2,n};
		}
		return {p.first,p.second+1};
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
	#endif
	
	cin >> n >> k;
	int carsLeft = 0;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
			if (2 <= i && i <= 3 && grid[i][j]) carsLeft++;
		}
	}

	//first try moving all to their spot
	for (int j = 1; j <= n; j++) {
		if (grid[2][j] && grid[1][j] == grid[2][j]) {
			//cout << grid[2][j] << ' ' << 1 << ' ' << j << '\n';
			ans.push_back({grid[2][j],1,j});
			grid[2][j] = 0;
			carsLeft--;
		}
	}

	for (int j = 1; j <= n; j++) {
		if (grid[3][j] && grid[3][j] == grid[4][j]) {
			//cout << grid[3][j] << ' ' << 4 << ' ' << j << '\n';
			ans.push_back({grid[3][j],4,j});
			grid[3][j] = 0;
			carsLeft--;
		}
	}

	//check if impossible
	if (carsLeft == 2*n) {
		cout << -1 << '\n';
		return 0;
	}

	//now continue going clockwise until all cars are done
	pair<int,int> curr = {2,1};
	while (carsLeft) {
		if (grid[curr.first][curr.second]) {
			if (curr.first == 2) {
				if (grid[2][curr.second] == grid[1][curr.second]) {
					//cout << grid[2][curr.second] << ' ' << 1 << ' ' << curr.second << '\n';
					ans.push_back({grid[2][curr.second],1,curr.second});
					grid[2][curr.second] = 0;
					carsLeft--;
				}
			}
			else if (curr.first == 3) {
				if (grid[3][curr.second] == grid[4][curr.second]) {
					//cout << grid[3][curr.second] << ' ' << 4 << ' ' << curr.second << '\n';zb
					ans.push_back({grid[3][curr.second],4,curr.second});
					grid[3][curr.second] = 0;
					carsLeft--;
				}
			}

			if (grid[curr.first][curr.second]) {
				pair<int,int> nxt = goCounter(curr);
				if (!grid[nxt.first][nxt.second]) {
					//cout << grid[curr.first][curr.second] << ' ' << nxt.first << ' ' << nxt.second << '\n';
					ans.push_back({grid[curr.first][curr.second],nxt.first,nxt.second});
					grid[nxt.first][nxt.second] = grid[curr.first][curr.second];
					grid[curr.first][curr.second] = 0;
				}	
			}
		}
		curr = goClock(curr);
	}

	//output
	cout << ans.size() << '\n';
	for (Move& m: ans) {
		cout << m.i << ' ' << m.r << ' ' << m.c << '\n';
	}	
	
	return 0;
}