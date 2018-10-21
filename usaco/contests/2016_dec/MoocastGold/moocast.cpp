/*
ID: silxikys
PROG: moocast
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

ofstream fout("moocast.out");
ifstream fin("moocast.in");

const int maxn = 1000;
int N;
int cows[maxn][2];
vector<int> distances;
int cowdistance[maxn][maxn];
vector<int> adjacents[maxn];
deque<pair<int,pair<int,int>>> distancelist;

void floodfill(int i,int& ncows,int visited[]) {
	if (adjacents[i].size() != 0) {
		ncows++;
	
		visited[i] = 1;
		for (int adj: adjacents[i]) {
			if (!visited[adj]) {
				floodfill(adj,ncows,visited);
			}
		}
	}
}

int main()
{
	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2; j++) {
			fin >> cows[i][j];
		}
	}

	//create distances
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			int d2 = (cows[i][0]-cows[j][0])*(cows[i][0]-cows[j][0])
			    +(cows[i][1]-cows[j][1])*(cows[i][1]-cows[j][1]);
			    cowdistance[i][j] = d2;
			    cowdistance[j][i] = d2;
			distances.push_back(d2);
			distancelist.push_back(make_pair(d2,make_pair(i,j)));
		}
	}


	int ans;
	sort(distances.begin(),distances.end());
	sort(distancelist.begin(),distancelist.end());
	int lasttried = 0;
	int ncows = 0;
	int visited[maxn] = {0};
	for (int d: distances) {
		if (d != lasttried) {
			/*
			for (int i = 0; i < N; i++) {
				//adjacents[i] = {};
				for (int j = i + 1; j < N; j++) {
					if (cowdistance[i][j] <= d && cowdistance[i][j] > lasttried) {
						adjacents[i].push_back(j);
						adjacents[j].push_back(i);
					}
				}
			}
			*/
			//update adjacents
			while (distancelist.front().first <= d) {
				int i = distancelist.front().second.first;
				int j = distancelist.front().second.second;
				adjacents[i].push_back(j);
				adjacents[j].push_back(i);

				distancelist.pop_front();
			}

			
			//try floodfill
			/*
			for (int i = 0; i < N; i++) {
				if (visited[i] == 0) {
					floodfill(i,ncows,visited);
					break;
				}
			}
			*/
			
			
			int ncows = 0;
			int visited[maxn] = {0};
			floodfill(0,ncows,visited);
			
			
			
			if (ncows == N) {
				ans = d;
				break;
			}
			
		}
		lasttried = d;
	}


	cout << ans << '\n';
	fout << ans << '\n';



	return 0;
}