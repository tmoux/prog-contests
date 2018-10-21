/*
ID: silxikys
PROG: cownav
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

ofstream fout("cownav.out");
ifstream fin("cownav.in");

const int maxn = 21;
bool grid[maxn][maxn];
int dp[maxn][maxn][4][maxn][maxn][4];
int N;
const int addDirection[4][2] = {{0,1},
								{1,0},
								{0,-1},
								{-1,0}};

pair<int,int> moveForward(int x, int y, int d) {
	if (x == N && y == N) {
		return make_pair(x,y);
	}
	int xprime = x+addDirection[d][0];
	int yprime = y+addDirection[d][1];
	if (xprime >= 1 && xprime <= N && yprime >= 1 && yprime <= N && !grid[xprime][yprime]) {
		return make_pair(xprime,yprime);
	}
	return make_pair(x,y);
}

struct State 
{
	int ax, ay, ad, bx, by, bd;

	vector<State> getNexts() {
		vector<State> ret;
		//forwards;
		pair<int,int> newAs = moveForward(ax,ay,ad);
		pair<int,int> newBs = moveForward(bx,by,bd);
		ret.push_back({newAs.first,newAs.second,ad,newBs.first,newBs.second,bd});
		ret.push_back({ax,ay,(ad+1)%4,bx,by,(bd+1)%4});
		ret.push_back({ax,ay,(ad+3)%4,bx,by,(bd+3)%4});
		
		return ret;
	}

	void print() {
		cout << ax << ' ' << ay << ' ' << ad << '\n' << bx << ' ' << by << ' ' << bd << "\n\n";
	}
};

int main() 
{
	fin >> N;
	for (int i = N; i >= 1; i--) {
		for (int j = 1; j <= N; j++) {
			char c; fin >> c;
			if (c == 'H') {
				grid[i][j] = true;
			}
		}
	}

	deque<State> deq = {{1,1,0,1,1,1}};
	dp[1][1][0][1][1][1] = 1;

	int ans;
	while (!deq.empty()) {
		State fi = deq.front();
		//fi.print();
		if (fi.ax == N && fi.ay == N && fi.bx == N && fi.by == N) {
			cout << "ok\n";
			ans = dp[fi.ax][fi.ay][fi.ad][fi.bx][fi.by][fi.bd] - 1;
			break;
		}

		for (State next: fi.getNexts()) {
			if (dp[next.ax][next.ay][next.ad][next.bx][next.by][next.bd] == 0) {
				dp[next.ax][next.ay][next.ad][next.bx][next.by][next.bd] = 
					dp[fi.ax][fi.ay][fi.ad][fi.bx][fi.by][fi.bd] + 1;
				deq.push_back(next);
			}
		}

		deq.pop_front();
	}

	cout << ans << '\n';
	fout << ans << '\n';

	/*
	State test = {1,3,0,3,1,0};
	for (State s: test.getNexts()) {
		s.print();
	}
	*/




	return 0;
}