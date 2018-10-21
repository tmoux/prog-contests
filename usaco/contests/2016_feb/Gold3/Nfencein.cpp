/*
ID: silxikys
PROG: fencedin
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

ofstream fout("fencedin.out");
ifstream fin("fencedin.in");

struct Edge
{
	int vertex[2][2];
	int weight;

	bool operator<(const Edge& rhs) const {
		return weight < rhs.weight;
	}
};

const int maxn = 2002;
int A, B, N, M;
int verticals[maxn];
int horizontals[maxn];
pair<int,int> parent[maxn][maxn];
int nodeRank[maxn][maxn];

pair<int,int> findParent(int i, int j) {
	if (parent[i][j] != make_pair(i,j)) {
		parent[i][j] = findParent(parent[i][j].first,parent[i][j].second);
	}
	return parent[i][j];
}
void makeUnion(pair<int,int> p1, pair<int,int> p2) {
	pair<int,int> p1Parent = findParent(p1.first,p1.second);
	pair<int,int> p2Parent = findParent(p2.first,p2.second);
	if (nodeRank[p1Parent.first][p1Parent.second] < nodeRank[p2Parent.first][p2Parent.second]) {
		parent[p1Parent.first][p1Parent.second] = make_pair(p2Parent.first,p2Parent.second);
	}
	else if (nodeRank[p2Parent.first][p2Parent.second] < nodeRank[p1Parent.first][p1Parent.second]) {
		parent[p2Parent.first][p2Parent.second] = make_pair(p1Parent.first,p1Parent.second);
	}
	else {
		parent[p2Parent.first][p2Parent.second] = make_pair(p1Parent.first,p1Parent.second);
		nodeRank[p1Parent.first][p1Parent.second]++;
	}
	
}

long long kruskal(Edge edges[], int size) {
	long long ret = 0;
	int numEdges = 0;
	for (int i = 0; i < size && numEdges < (((N+1)*(M+1))-1); i++) {
		Edge e = edges[i];
		pair<int,int> x = findParent(e.vertex[0][0],e.vertex[0][1]);
		pair<int,int> y = findParent(e.vertex[1][0],e.vertex[1][1]);
		
		if (x != y) {
			ret += e.weight;
			numEdges++;
			makeUnion(make_pair(e.vertex[0][0],e.vertex[0][1]),make_pair(e.vertex[1][0],e.vertex[1][1]));
		}

	}

	return ret;
}

int main() 
{
	fin >> A >> B >> N >> M;
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxn; j++) {
			parent[i][j] = make_pair(i,j);
		}
	}
	for (int i = 0; i < N; i++) {
		fin >> verticals[i];
	}
	for (int i = 0; i < M; i++) {
		fin >> horizontals[i];
	}
	sort(verticals,verticals+N);
	sort(horizontals,horizontals+M);
	verticals[N] = A;
	horizontals[M] = B;

	Edge edges[maxn*maxn*2];
	int index = 0;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			if (i != N) {
				Edge e;
				e.vertex[0][0] = i;
				e.vertex[0][1] = j;
				e.vertex[1][0] = i+1;
				e.vertex[1][1] = j;
				if (j == 0) {
					e.weight = horizontals[j];
				}
				else {
					e.weight = horizontals[j] - horizontals[j-1];
				}
				edges[index++] = e;
			}
			if (j != M) {
				Edge e;
				e.vertex[0][0] = i;
				e.vertex[0][1] = j;
				e.vertex[1][0] = i;
				e.vertex[1][1] = j+1;
				if (i == 0) {
					e.weight = verticals[i];
				}
				else {
					e.weight = verticals[i] - verticals[i-1];
				}
				edges[index++] = e;
			}
		}
	}
	
	sort(edges,edges+index);
	/*
	for (Edge e: edges) {
		cout << e.vertex[0].first << ' ' << e.vertex[0].second << '\n';
		cout << e.vertex[1].first << ' ' << e.vertex[1].second << '\n';
		cout << e.weight << "\n\n";
	}
	*/
	long long ans = kruskal(edges,index);
	cout << ans << '\n';
	fout << ans << '\n';
	return 0;
}