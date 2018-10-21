/*
ID: silxikys
PROG: milk6
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

const int maxn = 35;
int capacity[maxn][maxn];
const int infinity = 999999999;
int N, M;

struct Edge {
	int weight;
	int index;	
	int first;
	int second;
};

int getflow() {

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

		flow[1] = infinity;


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
			if (maxloc == N) {
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

		int pathcapacity = flow[N];
		totalflow += pathcapacity;

		int curnode = N;
		while (curnode != 1) {
			int nextnode = prevnode[curnode];
			ccopy[nextnode][curnode] -= pathcapacity;
			ccopy[curnode][nextnode] += pathcapacity; //reverse arc
			curnode = nextnode;
		}

	}
	return totalflow;
}

int main() {
	t1 = gettime();
	ofstream fout("milk6.out");
	ifstream fin("milk6.in");

	//input
	fin >> N >> M;
	vector<Edge> edges;
	for (int i = 1; i <= M; i++) {
		int si, ei, ci;
		fin >> si >> ei >> ci;
		capacity[si][ei] += ci;
		Edge e = {ci, i, si, ei};
		edges.push_back(e);
	}
	/*
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			//cout << capacity[i][j] << " ";
			cout << i << j << " ";
		} cout << '\n';
	}
	*/
	

	sort(edges.begin(), edges.end(), [](const Edge& lhs, const Edge& rhs)
	{
   			if (lhs.weight != rhs.weight) {
   				return lhs.weight > rhs.weight;
   			}
   			else {
   				return lhs.index < rhs.index;
   			}
	});
	/*
	for (Edge e: edges) {
		cout << e.weight << " " << e.index << endl;
	} cout << endl << endl;
	*/

	//try all edges to see if flow is less

	
	int currflow = getflow();
	vector<int> removes;
	int cost = 0;

	for (Edge e: edges) {
		capacity[e.first][e.second] -= e.weight;
		int newflow = getflow();
		//cout << e.index << " " << e.weight << " " << e.first << " " << e.second << " " << newflow << endl;
		//cout << newflow << " " << e.weight << " " << currflow << endl;
		if (newflow + e.weight == currflow) {
			//means it is good edge
			removes.push_back(e.index);
			cost += e.weight;
			currflow = newflow;

		}
		else {
			//add the edge back, not good edge
			capacity[e.first][e.second] += e.weight;
		}
		if (currflow == 0) {
		 	break;
		}
	}
	
	sort(removes.begin(),removes.end());
	cout << cost << " " << removes.size() << '\n';
	for (int i = 0; i < removes.size(); i++) {
		cout << removes[i] << '\n';
	}
	

	fout << cost << " " << removes.size() << '\n';
	for (int i = 0; i < removes.size(); i++) {
		fout << removes[i] << '\n';
	}
	
	
	endProgram(t1);
	return 0;
	
}