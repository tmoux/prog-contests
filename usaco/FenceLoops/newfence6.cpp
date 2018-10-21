/*
ID: silxikys
PROG: fence6
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>
#include <chrono>
#include <math.h>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

//globals
int N;
vector<int> adjacents[105];
int numNodes = 0;
map<pair<int,int>,int> mapping;
int dist[105][105];





int main() {
	t1 = gettime();
	ofstream fout("fence6.out");
	ifstream fin("fence6.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		int s, ls, n1, n2;
		fin >> s >> ls >> n1 >> n2;
		vector<int> v1 = {s}, v2 = {s};
		for (int j = 0; j < n1; j++) {
			int k; fin >> k;
			v1.push_back(k);
		}
		for (int j = 0; j < n2; j++) {
			int k; fin >> k;
			v2.push_back(k);
		}
		sort(v1.begin(),v1.end()); sort(v2.begin(),v2.end());
		pair<int,int> p1 = make_pair(v1[v1.size()-1],v1[v1.size()-2]);
		pair<int,int> p2 = make_pair(v2[v2.size()-1],v2[v2.size()-2]);
		if (mapping.find(p1) == mapping.end()) {
			mapping[p1] = mapping.size()-1;
			numNodes++;
		}
		if (mapping.find(p2) == mapping.end()) {
			mapping[p2] = mapping.size()-1;
			numNodes++;
		}

		adjacents[mapping[p1]].push_back(mapping[p2]);
		adjacents[mapping[p2]].push_back(mapping[p1]);
		dist[mapping[p1]][mapping[p2]] = ls;
		dist[mapping[p2]][mapping[p1]] = ls;
	}
	/*
	for (int i = 0; i < numNodes; i++) {
		for (int j : adjacents[i]) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			cout << dist[i][j] << " ";
		}
		cout << endl;
	} cout << endl << endl;
	*/
	

	//for each vertex and an adjacent vertex, remove the included edge and calculate the distance between the two vertices, and compare with the minimum so far
	int ans = 999999;

	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < adjacents[i].size(); j++) {
			vector<int> copyadjacents[105];
			for (int i = 0; i < numNodes; i++) {
				copyadjacents[i] = adjacents[i];
			}

			int jvertex = copyadjacents[i][j];
			//remove the adjacents
			copyadjacents[i].erase(copyadjacents[i].begin()+j);
			for (int k = 0; k < copyadjacents[jvertex].size(); k++) {
				if (copyadjacents[jvertex][k] == i) {
					copyadjacents[jvertex].erase(copyadjacents[jvertex].begin()+k);
					break;
				}
			}
			//dijkstra from vertex i to vertex jvertex
			vector<int> cost;
			cost.assign(numNodes,999999);
			vector<int> previous;
			previous.assign(numNodes,-1);
			cost[i] = 0;
			bool Q[105];
			int qsize = numNodes;
			for (int k = 0; k < numNodes; k++) {
				Q[k] = true;
			}
			while (qsize != 0) {
				int smallest = 999999;
				int u;
				for (int k = 0; k < numNodes; k++) {
					if (Q[k] == true) {
						if (cost[k] < smallest) {
							smallest = cost[k];
							u = k;
						}
					}
				}
				Q[u] = false;
				qsize--;
				
				if (u == jvertex) {
					break;
				}

				
				for (int v: copyadjacents[u]) {
					if (Q[v] == true) {
						int alt = cost[u] + dist[u][v];
						if (alt < cost[v]) {
							cost[v] = alt;
							previous[v] = u;
						}
					}
				}
			}

			//cout << i << " " << jvertex << " " << (cost[jvertex] + dist[i][jvertex]) << endl;		
			ans = min(ans,cost[jvertex]+dist[i][jvertex]);


			//add them back
			//adjacents[i].push_back(jvertex);
			//adjacents[jvertex].push_back(i);

		}
	}

	cout << ans << endl;
	fout << ans << endl;




	endProgram(t1);
	return 0;
}