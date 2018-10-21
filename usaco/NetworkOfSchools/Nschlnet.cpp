/*
ID: silxikys
PROG: schlnet
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
const int maxn = 103;
int N;
int network[maxn][maxn]; //network[i][j] -> j is a child of i
int condensate[maxn][maxn]; 
//condensate is a DAG where each node is a strongly connected component
vector<int> llist;
int visited[maxn];
int component[maxn];

void visit(int u) {
	if (!visited[u]) {
		visited[u] = 1;
		for (int v = 1; v <= N; v++) {
			if (network[u][v]) {
				visit(v);
			}
		}
		llist.push_back(u);
	}
}

void assign(int u, int root) {
	if (!component[u]) {
		component[u] = root;
		for (int v = 1; v <= N; v++) {
			if (network[v][u]) {
				assign(v,root);
			}
		}
	}
}

int main() {
	t1 = gettime();
	ofstream fout("schlnet.out");
	ifstream fin("schlnet.in");

	//input
	fin >> N;
	for (int i = 1; i <= N; i++) {
		int child;
		while (true) {
			fin >> child;
			if (!child)
				break;
			network[i][child] = 1;
		}
	}
	/*
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << network[i][j] << ' ';
		} cout << '\n';
	}
	*/


	for (int u = 1; u <= N; u++) {
		visit(u);
	}
	int compNum = 1;
	for (int i = llist.size() - 1; i >= 0; i--) {
		int u = llist[i];
		if (!component[u]) {
			assign(u,compNum);
			compNum++;
		}
	}	
	/* //print component numbers for each node
	for (int i = 1; i <= N; i++) {
		cout << i << ' ' << component[i] << '\n';
	}
	*/

	for (int u = 1; u <= N; u++) {
		for (int v = 1; v <= N; v++) {
			if (component[u] != component[v] && network[u][v]) {
				condensate[component[u]][component[v]] = 1;
			}
		}
	}

	/*
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << condensate[i][j] << ' ';
		} cout << '\n';
	}
	*/
	//now condensate DAG is done, now compute sources/sinks
	int sccs = compNum - 1;
	int sources = 0, sinks = 0;
	for (int u = 1; u <= sccs; u++) {
		bool issource = true, issink = true;
		for (int v = 1; v <= sccs; v++) {
			if (condensate[v][u]) {
				issource = false;
			}
			if (condensate[u][v]) {
				issink = false;
			}
		}
		if (issource) {
			sources++;
		}
		if (issink) {
			sinks++;
		}
	}

	int taska = sources;
	int taskb;
	if (sccs == 1) {
		taskb = 0;
	}
	else {
		taskb = max(sources,sinks);
	}
	
	cout << taska << '\n' << taskb << '\n';
	fout << taska << '\n' << taskb << '\n';
	
	endProgram(t1);
	return 0;
}