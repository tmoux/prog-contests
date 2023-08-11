#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pp = pair<pair<int,int>,int>;

const int maxn = 1005;
int n, m, p, s[maxn];
char grid[maxn][maxn];
deque<pp> qs[maxn];
deque<pp> nexts[maxn];
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

bool valid(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m;
}

int ans[10];

int main()
{
	cin >> n >> m >> p;
	for (int i = 1; i <= p; i++) cin >> s[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
			if (1 <= grid[i][j]-'0' && grid[i][j]-'0' <= p) {
				qs[grid[i][j]-'0'].push_back({{i,j},s[grid[i][j]-'0']});
			}
		}
	}
	while (true) {
		bool done = true;
		for (int i = 1; i <= p; i++) if (!qs[i].empty()) done = false;
		if (done) break;
		for (int i = 1; i <= p; i++) {
			while (!qs[i].empty()) {
				pp f = qs[i].front(); qs[i].pop_front();
				int x = f.first.first;
				int y = f.first.second;
				if (grid[x][y] == '.') {
					grid[x][y] = (char)('0'+i);
				}
				else if (grid[x][y] != (char)('0'+i)) continue;
				if (grid[x][y] == (char)('0'+i)) {
					int d = f.second;
					for (int k = 0; k < 4; k++) {
						int nx = x + dx[k];
						int ny = y + dy[k];
						if (!valid(nx,ny)) continue;
						if (grid[nx][ny] == '.') {
							if (d > 0) {
								/*
								if (i == 2) {
									cout << nx << ' ' << ny << '\n';
								}
								*/
								grid[nx][ny] = (char)('0'+i);
								qs[i].push_back({{nx,ny},d-1});
							}
							else {
								nexts[i].push_back({{nx,ny},s[i]-1});
							}
						}
					}
				}
			}
			
		}
		for (int i = 1; i <= p; i++) {
			for (pp& nxt: nexts[i]) {
				int x = nxt.first.first;
				int y = nxt.first.second;
				if (grid[x][y] == '.') {
					qs[i].push_back(nxt);
				}
			}	
			sort(qs[i].begin(),qs[i].end());
			qs[i].erase(unique(qs[i].begin(),qs[i].end()),qs[i].end());
			nexts[i] = deque<pp>();
		}
		//debug
		/*
		for (int a = 0; a < n; a++) {
			for (int b = 0; b < m; b++) {
				cout << grid[a][b];
			}
			cout << '\n';
		}
		for (int i = 1; i <= p; i++) {
			cout << i << ": \n";
			for (auto q: qs[i]) {
				printf("(%d, %d): %d, %c\n",q.first.first,q.first.second,q.second,grid[q.first.first][q.first.second]);
			}
			
		}
		cout << "\n";
		*/
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int c = grid[i][j] - '0';
			if (1 <= c && c <= p) {
				ans[c]++;
			}
		}
	}
	for (int i = 1; i <= p; i++) {
		cout << ans[i] << ' ';
	}
	
	
	
	
	
	return 0;
}