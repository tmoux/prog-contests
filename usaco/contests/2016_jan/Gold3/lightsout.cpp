/*
ID: silxikys
PROG: lightsout
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
using namespace std;

ofstream fout("lightsout.out");
ifstream fin("lightsout.in");

const int maxn = 202;
int N;
pair<int,int> vertices[maxn];
int distToExit[maxn];
int edgeDistance[maxn];
int prefixPerim[maxn];
int isConvex[maxn]; //0 is not convex, 1 is not convex
int perimeter = 0;
map<vector<int>,int> mapping;

int findEdgeDistance(const pair<int,int>& p1, const pair<int,int>& p2) {
	return abs(p1.first-p2.first) + abs(p1.second-p2.second);
}

int main() 
{
	fin >> N;
	memset(distToExit, -1, sizeof(distToExit));
	for (int i = 0; i < N; i++) {
		int a, b; fin >> a >> b;
		vertices[i] = make_pair(a,b);
		if (i != 0) {
			edgeDistance[i] = findEdgeDistance(vertices[i],vertices[i-1]);
		}
	}
	edgeDistance[0] = findEdgeDistance(vertices[0],vertices[N-1]);

	for (int i = 0; i < N; i++) {
		perimeter += edgeDistance[i];
		if (i == 0) {
			prefixPerim[i] = 0;
		}
		else {
			prefixPerim[i] = prefixPerim[i-1] + edgeDistance[i];
		}
	}
	for (int i = 0; i < N; i++) {
		distToExit[i] = min(prefixPerim[i],perimeter-prefixPerim[i]);
	}

	for (int i = 0; i < N; i++) {
		pair<int,int> curr = vertices[i];
		pair<int,int> prev = vertices[(i-1+N)%N];
		pair<int,int> next = vertices[(i+1)%N];
		if (prev.first < curr.first && next.second < curr.second) {
			isConvex[i] = 1;
		}
		else if (prev.first > curr.first && next.second > curr.second) {
			isConvex[i] = 1;
		}
		else if (prev.second < curr.second && next.first > curr.first) {
			isConvex[i] = 1;
		}
		else if (prev.second > curr.second && next.first < curr.first) {
			isConvex[i] = 1;
		}
	}

	for (int i = 1; i < N; i++) {
		vector<int> adding = {isConvex[i]};
		mapping[adding]++;
		for (int j = i + 1; j <= N; j++) {
			int ji = j % N;
			adding.push_back(edgeDistance[ji]);
			adding.push_back(isConvex[ji]);
			mapping[adding]++;
		}
	}
	/*
	for (pair<vector<int>,int> p: mapping) {
		for (int i: p.first) {
			cout << i << ' ';
		}
		cout << ": " << p.second << '\n';
	}
	*/
	int worstcase = 0;
	for (int i = 1; i < N; i++) {
		vector<int> testing = {isConvex[i]};
		int amtTraveled = 0;
		if (mapping[testing] == 1) {
			amtTraveled += distToExit[i];
		}
		else {
			for (int j = i + 1; j <= N; j++) {
				int ji = j % N;
				testing.push_back(edgeDistance[ji]);
				testing.push_back(isConvex[ji]);
				amtTraveled += edgeDistance[ji];
				if (mapping[testing] == 1) {
					//found solution
					amtTraveled += distToExit[ji];
					break;	
				}
			}
		}
		
		int distChange = amtTraveled - distToExit[i];
		worstcase = max(worstcase,distChange);
	}

	cout << worstcase << '\n';
	fout << worstcase << '\n';
	
	return 0;
}