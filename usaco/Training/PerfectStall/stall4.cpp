/*
ID: silxikys
PROG: stall4
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

int M, N;
const int maxn = 420;
const int infinity = 999999;
int capacity[maxn][maxn];



int main() {
	t1 = gettime();
	ofstream fout("stall4.out");
	ifstream fin("stall4.in");

	//input
	fin >> N >> M;
	int source = 1;
	int sink = M + N + 2;
	for (int i = 2; i <= N+1; i++) {
		int si; fin >> si;
		capacity[source][i] = 1;
		for (int j = 0; j < si; j++) {
			int stall; fin >> stall;
			capacity[i][stall+N+1] = 1;
		}
	}
	for (int stall = N+2; stall <= M+N+1; stall++) {
		capacity[stall][sink] = 1;
	}

	/*
	for (int i = source; i <= sink; i++) {
		for (int j = source; j <= sink; j++) {
			cout << capacity[i][j] << " ";
		} cout << endl;
	}
	*/
	

	//network flow algorithm
	int totalflow = 0;

	while (true) {
		int prevnode[maxn];
		int flow[maxn];
		bool visited[maxn];
		int maxloc = 0;


		
		for (int i = source; i <= sink; i++) {
			prevnode[i] = 0; //0 = "nil"
			flow[i] = 0;
			visited[i] = false;
		}

		flow[source] = infinity;

		

		while (true) {
			int maxflow = 0;
			maxloc = 0; //0 = "nil"
			//find the unvisited node with the highest capacity to it 
			for (int i = source; i <= sink; i++) {
				if (flow[i] > maxflow && visited[i] == false) {
					maxflow = flow[i];
					maxloc = i;
				}
			}
			if (maxloc == 0) {
				break;
			}
			if (maxloc == sink) {
				break;
			}
			visited[maxloc] = true;
			//update neighbors of maxloc
			for (int i = source; i <= sink; i++) {
				if (capacity[maxloc][i] > 0) {
					if (flow[i] < min(maxflow,capacity[maxloc][i])) {
						prevnode[i] = maxloc;
						flow[i] = min(maxflow,capacity[maxloc][i]);
					}
				}
			}
		}

		if (maxloc == 0) {
			break;
		}

		int pathcapacity = flow[sink];
		totalflow += pathcapacity;


		int curnode = sink;
		while (curnode != source) {
			int nextnode = prevnode[curnode];
			capacity[nextnode][curnode] -= pathcapacity;
			capacity[curnode][nextnode] += pathcapacity; //reverse arc
			curnode = nextnode;
		}

	}

	cout << totalflow << endl;
	fout << totalflow << endl;


	
	endProgram(t1);
	return 0;
}