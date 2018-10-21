/*
ID: silxikys
PROG: dream
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <deque>
using namespace std;

ofstream fout("dream.out");
ifstream fin("dream.in");
const int maxn = 1000;
int N, M;
int mindist[maxn][maxn][4][2];
int board[maxn][maxn];
const int dy[4] = {0,1,0,-1};
const int dx[4] = {-1,0,1,0};
struct State
{
	int x;
	int y;
	int dir;
	int smell;
};

vector<State> getNexts(State curr) {
	vector<State> ret;
	bool isCurrDirClear = true;
	int nxx = curr.x + dx[curr.dir];
	int nyy = curr.y + dy[curr.dir];
	if (!(board[curr.x][curr.y] == 4 && nxx >= 0 && nxx < N && nyy >= 0 && nyy < M &&	!(board[nxx][nyy] == 3 && curr.smell == 0) && board[nxx][nyy] != 0)) {
		isCurrDirClear = false;
	}
	for (int i = 0; i < 4; i++) {
		int nx = curr.x + dx[i];
		int ny = curr.y + dy[i];


		if (nx >= 0 && nx < N && ny >= 0 && ny < M && !(board[nx][ny] == 3 && curr.smell == 0) && board[nx][ny] != 0 && (board[curr.x][curr.y] != 4 || i == curr.dir || !isCurrDirClear)) {
			int nSmell = curr.smell;
			if (board[nx][ny] == 2) {
				nSmell = 1;
			}
			else if (board[nx][ny] == 4) {
				nSmell = 0;
			}
			ret.push_back({nx,ny,i,nSmell});
		}
	}
	return ret;
}

int main() 
{
	fin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			fin >> board[i][j];
		}
	}

	deque<State> deq = {{0,0,1,0},{0,0,2,0}};
	for (State s: deq) {
		mindist[s.x][s.y][s.dir][s.smell] = 1;
	}
	
	
	int ans = -1;
	while (!deq.empty()) {
		State s = deq.front();
		//cout << s.x << ' ' << s.y << ' ' << s.dir << ' ' << s.smell << '\n';
		if (s.x == N - 1 && s.y == M - 1) {
			ans = mindist[s.x][s.y][s.dir][s.smell] - 1;
			break;
		}
		for (State ns: getNexts(s)) {
			if (mindist[ns.x][ns.y][ns.dir][ns.smell] == 0) {
				mindist[ns.x][ns.y][ns.dir][ns.smell] = 
				mindist[s.x][s.y][s.dir][s.smell] + 1;
				deq.push_back(ns);
			}
		}

		deq.pop_front();
	}
	
	cout << ans << '\n';
	fout << ans << '\n';
	

	return 0;
}