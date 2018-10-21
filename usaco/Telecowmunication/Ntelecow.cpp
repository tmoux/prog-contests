/*
ID: silxikys
PROG: telecow
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

int getflow(int source, int sink, int N, int maxn);

const int maxn = 105*2;
int capacity[maxn][maxn];
const int infinity = 999999999;
int c1, c2;
int N, M;


int main() {
	t1 = gettime();
	ofstream fout("telecow.out");
	ifstream fin("telecow.in");

	//input
	
	fin >> N >> M >> c1 >> c2;
	N *= 2;
	c1 = c1*2;
	c2 = c2*2 - 1;
	for (int i = 0; i < M; i++) {
		int a, b; fin >> a >> b;
		capacity[2*a][2*b-1] = 1;
		capacity[2*a-1][2*a] = 1;

		capacity[2*b][2*a-1] = 1;
		capacity[2*b-1][2*b] = 1;
	}

	cout << c1 << ' ' << c2 << endl;
	vector<int> removes;
	int curflow = getflow(c1, c2, N, maxn);
	
	for (int node = 2; node <= N; node+=2) {
		if (node != c1 && node != c2 + 1) {
			//remove edges and see if flow decreases
			vector<int> addbacks;
			for (int i = 1; i <= N; i++) {
				if (capacity[node][i]) {
					addbacks.push_back(i);
					capacity[node][i] = 0;
				}
			capacity[node-1][node] = 0; //cuts off input node


			}
			int newflow = getflow(c1, c2, N, maxn );
			
			if (newflow < curflow) {
				removes.push_back(node/2);
				curflow = newflow;
			}
			else {
				//add it back
				for (int i : addbacks) {
					capacity[node][i] = 1;
				}
				capacity[node-1][node] = 1;
			}
			if (curflow == 0) {
				break;
			}
		}
	}
	
	//output
	cout << removes.size() << '\n';
	fout << removes.size() << '\n';
	for (int i = 0; i < removes.size(); i++) {
		cout << removes[i];
		fout << removes[i];
		if (i < removes.size() - 1) {
			cout << ' ';
			fout << ' ';
		}
		else {
			cout << '\n';
			fout << '\n';
		}
	}

	
	endProgram(t1);
	return 0;
	
}

/*
getflow(source, sink) takes in a global two-dimensional array (capacity) 
and two integers, which represent the nodes that are the source and the sink.
Other variables: N is the number of nodes
			     maxn is the maximum size of capacity and also N
Everything else should be perfectly self-contained. The only global variable needed is the 2-d array capacity
returns an int, the total flow from the source to the sink
*/
int getflow(int source, int sink, int N, int maxn) {
	int totalflow = 0;
	int ccopy[maxn][maxn];
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ccopy[i][j] = capacity[i][j];
		}
	}
	while (true) {
		int prevnode[maxn];
		int flow[maxn];
		bool visited[maxn];
		int maxloc = 0;
		
		for (int i = 1; i <= N; i++) {
			prevnode[i] = 0; //0 = "nil"
			flow[i] = 0;
			visited[i] = false;
		}

		flow[source] = infinity;


		while (true) {
			int maxflow = 0;
			maxloc = 0; //0 = "nil"
			//find the unvisited node with the highest capacity to it 
			for (int i = 1; i <= N; i++) {
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
			for (int i = 1; i <= N; i++) {
				if (ccopy[maxloc][i] > 0) {
					if (flow[i] < min(maxflow,ccopy[maxloc][i])) {
						prevnode[i] = maxloc;
						flow[i] = min(maxflow,ccopy[maxloc][i]);
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
			ccopy[nextnode][curnode] -= pathcapacity;
			ccopy[curnode][nextnode] += pathcapacity; //reverse arc
			curnode = nextnode;
		}

	}
	return totalflow;
}