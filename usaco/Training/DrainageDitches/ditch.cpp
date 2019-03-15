/*
ID: silxikys
PROG: ditch
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
const int maxm = 205;
const int infinity = 999999999;
int capacity[maxm][maxm];


int main() {
	t1 = gettime();
	ofstream fout("ditch.out");
	ifstream fin("ditch.in");

	//input
	fin >> N >> M;
	for (int i = 0; i < N; i++) {
		int si, ei, ci; fin >> si >> ei >> ci;
		capacity[si][ei] += ci;
	}

	//network flow algorithm
	int totalflow = 0;

	while (true) {
		int prevnode[maxm];
		int flow[maxm];
		bool visited[maxm];
		int maxloc = 0;
		
		for (int i = 1; i <= M; i++) {
			prevnode[i] = 0; //0 = "nil"
			flow[i] = 0;
			visited[i] = false;
		}

		flow[1] = infinity;


		while (true) {
			int maxflow = 0;
			maxloc = 0; //0 = "nil"
			//find the unvisited node with the highest capacity to it 
			for (int i = 1; i <= M; i++) {
				if (flow[i] > maxflow && visited[i] == false) {
					maxflow = flow[i];
					maxloc = i;
				}
			}
			if (maxloc == 0) {
				break;
			}
			if (maxloc == M) {
				break;
			}
			visited[maxloc] = true;
			//update neighbors of maxloc
			for (int i = 1; i <= M; i++) {
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

		int pathcapacity = flow[M];
		totalflow += pathcapacity;

		int curnode = M;
		while (curnode != 1) {
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
