/*
ID: silxikys
PROG: mootube
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

ofstream fout("mootube.out");
ifstream fin("mootube.in");

struct Edge 
{
	int otherNode;
	int relevance;
};

const int maxn = 100002;
vector<Edge> adjacents[maxn];
int N, Q;

int countVideos(int i, int vi, int ki) {
	int total = 1;
	for (Edge& j: adjacents[i]) {
		if (j.otherNode != vi && j.relevance >= ki) {
			total += countVideos(j.otherNode,i,ki);
		} 
	}
	return total;
}

void printQuery(int ki, int vi) {
	int total = 0;
	for (Edge& i: adjacents[vi]) {
		if (i.relevance >= ki) {
			total += countVideos(i.otherNode,vi,ki);
		}
		
	}
	cout << total << '\n';
	fout << total << '\n';
}

int main() 
{
	fin >> N >> Q;
	for (int i = 0; i < N - 1; i++) {
		int pi, qi, ri; fin  >> pi >> qi >> ri;
		adjacents[pi].push_back({qi,ri});
		adjacents[qi].push_back({pi,ri});
	}

	for (int i = 0; i < Q; i++) {
		int ki, vi; fin >> ki >> vi;
		printQuery(ki,vi);
	}



	return 0;
}