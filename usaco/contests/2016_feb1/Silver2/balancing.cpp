/*
ID: silxikys
PROG: balancing
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

ofstream fout("balancing.out");
ifstream fin("balancing.in");

const int maxn = 1000;

pair<int,int> sortxs[maxn];
pair<int,int> sortys[maxn];

int N;

struct Regions {
	int upleft;
	int upright;
	int downleft;
	int downright;
};
Regions matr[maxn][maxn];

int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		int x, y; fin >> x >> y;
		sortxs[i] = make_pair(x,y);
		sortys[i] = make_pair(x,y);
	}

	sort(sortxs,sortxs+N);
	sort(sortys,sortys+N, [](const pair<int,int>& left, const pair<int,int>& right) {
		return left.second < right.second;
	} );
	/*
	for (int i = 0; i < N; i++) {
		cout << sortxs[i].first << ' ' << sortxs[i].second << '\n';
	}
	*/
	
	vector<pair<int,int>> verticals, horizontals;
	int xcoord = sortxs[0].first;
	verticals.push_back(make_pair(xcoord,1));
	
	for (int i = 1; i < N; i++) {
		pair<int,int> p = sortxs[i];
		if (p.first == verticals[verticals.size()-1].first) {
			verticals[verticals.size()-1].second++;
		}
		else {
			verticals.push_back(make_pair(p.first,verticals[verticals.size()-1].second+1));
		}
	}

	int ycoord = sortys[0].second;
	horizontals.push_back(make_pair(ycoord,1));

	for (int i = 1; i < N; i++) {
		pair<int,int> p = sortys[i];
		if (p.second == horizontals[horizontals.size()-1].first) {
			horizontals[horizontals.size()-1].second++;
		}
		else {
			horizontals.push_back(make_pair(p.second,horizontals[horizontals.size()-1].second+1));
		}
	}


	for (int i = 0; i < verticals.size(); i++) {
		pair<int,int> vert = verticals[i];
		for (int j = 0; j < horizontals.size(); j++) {
			pair<int,int> horiz = horizontals[j];
			if (i == 0 && j == 0) {
				for (int a = 0; a < N; a++) {
					pair<int,int> p = sortxs[a];
					if (p.first <= vert.first) {
						if (p.second <= horiz.first) {
							matr[i][j].downleft++;
						}
						else {
							matr[i][j].downright++;
						}
					}
					else {
						if (p.second <= horiz.first) {
							matr[i][j].upleft++;
						}
						else {
							matr[i][j].upright++;
						}
					}
				}
			}
		}
	}

	




	return 0;
}