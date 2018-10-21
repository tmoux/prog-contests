/*
ID: silxikys
PROG: visitfj
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <set>
using namespace std;

ofstream fout("visitfj.out");
ifstream fin("visitfj.in");

struct Point
{
	int row;
	int col;
	int state;

	bool operator<(const Point& rhs) const {
		if (row != rhs.row) {
			return row < rhs.row;
		}
		if (col != rhs.col) {
			return col < rhs.col;
		}
		if (state != rhs.state) {
			return state < rhs.state;
		}
	}
};

const int maxn = 100;
int N, T;
int graph[maxn][maxn][3]; //0 is eat the food

vector<Point> getAdjacents(Point p)
{
	vector<Point> ret;
	if (p.row > 0) {
		ret.push_back({p.row-1,p.col,(p.state+1) % 3});
	}
	if (p.row < N - 1) {
		ret.push_back({p.row+1,p.col,(p.state+1) % 3});
	}
	if (p.col > 0) {
		ret.push_back({p.row,p.col-1,(p.state+1) % 3});
	}
	if (p.col < N - 1) {
		ret.push_back({p.row,p.col+1,(p.state+1) % 3});
	}
	return ret;
}

int dijkstra(Point source) {
	int dist[maxn][maxn][3];
	memset(dist,0,sizeof(dist));
	set<pair<int,Point>> Q;
	const int INF = 2000000000;


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < 3; k++) {
				dist[i][j][k] = INF;
				Point toInsert = {i,j,k};
				Q.insert(make_pair(dist[i][j][k],toInsert));
			}
		}
	}

	dist[source.row][source.col][source.state] = 0;
	Q.insert(make_pair(0,source));

	while (!Q.empty()) 
	{
		pair<int,Point> tmp = *Q.begin();
		Q.erase(Q.begin());
		Point u = tmp.second;

		for (Point v: getAdjacents(u)) {
			int weight = graph[v.row][v.col][v.state];
			if (dist[v.row][v.col][v.state] > dist[u.row][u.col][u.state] + weight) {
				if (dist[v.row][v.col][v.state] != INF) {
					Q.erase(make_pair(dist[v.row][v.col][v.state],v));
				}
				dist[v.row][v.col][v.state] = dist[u.row][u.col][u.state] + weight;
				Q.insert(make_pair(dist[v.row][v.col][v.state],v));
			}
		}		
	}
	int mindist = min(dist[N-1][N-1][0],
				  min(dist[N-1][N-1][1],
					  dist[N-1][N-1][2]));
	return mindist;
}

int main() 
{
	//input
	fin >> N >> T;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int a; fin >> a;
			for (int k = 0; k < 3; k++) {
				graph[i][j][k] = T;
				if (k == 0) {
					graph[i][j][k] += a;
				}
			}
		}
	}

	int ans = dijkstra({0,0,0});
	fout << ans << '\n';
	cout << ans << '\n';





	return 0;
}