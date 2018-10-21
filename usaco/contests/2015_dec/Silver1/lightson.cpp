/*
ID: silxikys
PROG: lightson
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

ofstream fout("lightson.out");
ifstream fin("lightson.in");

const int maxn = 101;
vector<pair<int,int>> lights[maxn][maxn];
int N, M;
bool isLit[maxn][maxn];
bool visited[maxn][maxn];

void floodfill(int x, int y) {
	//cout << x << ' ' << y << '\n';
	if (visited[x][y]) return;
	visited[x][y] = true;
	for (pair<int,int> p: lights[x][y]) {
		if (!isLit[p.first][p.second]) {
			isLit[p.first][p.second] = true;
			if (((p.second < N && visited[p.first][p.second+1]) ||
				 (p.second > 1 && visited[p.first][p.second-1]) ||
				 (p.first < N && visited[p.first+1][p.second]) ||
				 (p.first > 1 && visited[p.first-1][p.second]))) {
				floodfill(p.first,p.second);
			}
		}
		
	}
	//right
	if (y < N) {
		if (isLit[x][y+1]) {
			floodfill(x,y+1);
		}
	}
	//left
	if (y > 1) {
		if (isLit[x][y-1]) {
			floodfill(x,y-1);
		}
	}
	//down
	if (x < N) {
		if (isLit[x+1][y]) {
			floodfill(x+1,y);
		}
	}
	//up
	if (x > 1) {
		if (isLit[x-1][y]) {
			floodfill(x-1,y);
		}
	}
}



int main() 
{
	fin >> N >> M;
	for (int i = 0; i < M; i++) {
		int x, y, a, b;
		fin >> x >> y >> a >> b;
		lights[x][y].push_back(make_pair(a,b));
	}
	/*
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << i << ' ' << j << ": ";
			for (pair<int,int> a: lights[i][j]) {
				cout << a.first << ' ' << a.second << ' ';
			}
			cout << '\n';
		} 
	}
	*/
	/*
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			isLit[i][j] = false;
			visited[i][j] = false;
			visi[i][j] = false;
		}
	}
	*/	

	isLit[1][1] = true;
	floodfill(1,1);
	
	//output based on isLit matrix

	int ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << isLit[i][j] << ' ';
			if (isLit[i][j]) ans++;
		} cout << '\n';
	}
	
	
	
	

	cout << ans << '\n';
	fout << ans << '\n';

	return 0;
}